% 程式初始化
% 讀取目標區域的局部特徵
% 分析目標區域的結構特徵

clear all
clc

% function 
% self_feature_selection: 特徵點篩選
% sampleROIAnalysis: 分析特定區域性質

% 操作

% 把相應的應用初始註解掉 還要記得去改 optics_clustering.m 裡面最上面的分群參數
% 若要執行車牌應用，須置換 ROI_extract 檔案
% 去 main 執行選擇的應用

global ref_descriptors;     % 篩選後的特徵點
global ref_locations;       % 篩選後的特徵點座標
global ROI_property;        % 篩選後的特徵點座標

global number_of_object;    % ROI物體總數之全域變數

% invoice
%
[ ref_descriptors ref_locations ] = self_feature_selection('dataset/invoice.bmp', 300);  % filter to 300 feature point
ROI_property = sampleROIAnalysis( imread('dataset/ROI/invoice_ROI.jpg') );
number_of_object = size(ROI_property.representation_of_components,1); 
%}


% banknote
%{
[ ref_descriptors ref_locations ] = self_feature_selection('dataset/banknote.bmp', 300);  % filter to 300 feature point
ROI_property = sampleROIAnalysis( imread('dataset/ROI/banknote_ROI.bmp') );
number_of_object = size(ROI_property.representation_of_components,1);
%}


% car plate
%{
[ ref_descriptors ref_locations ] = self_feature_selection('dataset/car plate.bmp', 300);  % filter to 300 feature point
ROI_property = sampleROIAnalysis( imread('dataset/ROI/car plate ROI.bmp') );
number_of_object = size(ROI_property.representation_of_components,1) - 1; % 數字與英文中間符號忽略
%}

