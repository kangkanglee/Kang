# -*- coding: utf-8 -*-
"""
Created on Sun Oct  2 19:55:10 2016

@author: kang
"""

import numpy as np
import pandas as pd
import xgboost as xgb

train_data = pd.read_csv("./input/train.csv", header=None, names = ['CONS_NO', 'outcome'])
test_data  = pd.read_csv("./input/test.csv", header=None, names = ['CONS_NO'])
#people_data  = pd.read_csv("./input/all_user_yongdian_data_2015.csv", dtype={'DATA_DATE': np.datetime64}, parse_dates=['DATA_DATE'])
people_data  = pd.read_csv("./input/all_user_yongdian_data_2015.csv", parse_dates=['DATA_DATE'])

train = train_data.merge(people_data, on='CONS_NO', how='left', left_index=True)
test  = test_data.merge(people_data, on='CONS_NO', how='left', left_index=True)

train=train.sort_values(by=['CONS_NO', 'DATA_DATE'], ascending=[True,True])
test=test.sort_values(by=['CONS_NO', 'DATA_DATE'], ascending=[True, True])

train = train.drop_duplicates(['CONS_NO', 'DATA_DATE'])
test = test.drop_duplicates(['CONS_NO', 'DATA_DATE'])

train = train.pivot('CONS_NO','DATA_DATE','KWH')
test = test.pivot('CONS_NO','DATA_DATE','KWH')

train['CONS_NO']=train.index
test['CONS_NO']=test.index

train = train.merge(train_data, on='CONS_NO', how='left', left_index=True)

train=pd.concat([train],ignore_index=True)
test=pd.concat([test],ignore_index=True)

label = train['outcome']
train = train.drop('outcome', axis=1)

########################################

dtrain = xgb.DMatrix(train,label=label)
dtest = xgb.DMatrix(test)

param = {'max_depth':10, 'eta':0.02, 'silent':1, 'objective':'binary:logistic' }
param['nthread'] = 4
param['eval_metric'] = 'auc'
param['subsample'] = 0.7
param['colsample_bytree']= 0.7
param['min_child_weight'] = 0
param['booster'] = "gbtree"

watchlist  = [(dtrain,'train')]
num_round = 150
early_stopping_rounds=10
bst = xgb.train(param, dtrain, num_round, watchlist,early_stopping_rounds=early_stopping_rounds)

ypred = bst.predict(dtest)
output = pd.DataFrame({ 'CONS_NO' : test['CONS_NO'], 'outcome': ypred })
output.head()
result = output.sort_values(by=['outcome'], ascending=[False])
result = result['CONS_NO']
result.to_csv('result.csv', index = False)
