% �{����l��
% Ū���ؼаϰ쪺�����S�x
% ���R�ؼаϰ쪺���c�S�x

clear all
clc

% function 
% self_feature_selection: �S�x�I�z��
% sampleROIAnalysis: ���R�S�w�ϰ�ʽ�

% �ާ@

% ����������Ϊ�l���ѱ� �٭n�O�o�h�� optics_clustering.m �̭��̤W�������s�Ѽ�
% �Y�n���樮�P���ΡA���m�� ROI_extract �ɮ�
% �h main �����ܪ�����

global ref_descriptors;     % �z��᪺�S�x�I
global ref_locations;       % �z��᪺�S�x�I�y��
global ROI_property;        % �z��᪺�S�x�I�y��

global number_of_object;    % ROI�����`�Ƥ������ܼ�

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
number_of_object = size(ROI_property.representation_of_components,1) - 1; % �Ʀr�P�^�夤���Ÿ�����
%}

