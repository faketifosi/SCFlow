% main
% �{������D�禡

%
% �Ϥ��s�ɥh����覡
% imshow(I,'Border','tight', 'initialmagnification', 'fit');
% print -depsc 'Filename.eps'

%%
% invoice
%

files=dir('test sample\invoice image\*.jpg');

global fig_handle;
global file;

for i = 1:size(files,1)  

    file = i
    SIFT_clustering_ROI( strcat('test sample\invoice image\', files(i).name) );
    
    % �̫ᵲ�G�x�s�� eps �ɮ�
    %print( fig_handle, strcat('test sample\invoice image\saveas\', num2str(i), '.eps'), '-depsc' );
    % �̫ᵲ�G�x�s�� jpg �ɮ�
    saveas(fig_handle, strcat('test sample\invoice image\saveas\', num2str(i), '.jpg') );       
end

%}


%%
% banknote
%{

files=dir('test sample\banknote image\*.jpg');

global fig_handle;
global file;

for i = 32%1:size(files,1) 
    
    file = i 
    SIFT_clustering_ROI( strcat('test sample\banknote image\', files(i).name) );
    
    % �̫ᵲ�G�x�s�� eps �ɮ�
    %print( fig_handle, strcat('test sample\banknote image\saveas\', num2str(i), '.eps'), '-depsc' );
    % �̫ᵲ�G�x�s�� jpg �ɮ�
    saveas(fig_handle, strcat('test sample\banknote image\saveas\', num2str(i), '.jpg') );

end

%}


%%
% car plate
%{

files=dir('test sample\car plate dataset\*.jpg');

global fig_handle;
global file;

for i = 1:size(files,1)   

    file = i
    SIFT_clustering_ROI( strcat('test sample\car plate dataset\', files(i).name) );    
    
    % �̫ᵲ�G�x�s�� eps �ɮ�
    %print( fig_handle, strcat('test sample\car plate dataset\saveas\', num2str(i), '.eps'), '-depsc' );
    % �̫ᵲ�G�x�s�� jpg �ɮ�
    saveas(fig_handle, strcat('test sample\car plate dataset\saveas\', num2str(i), '.jpg') );       
end

%}

axis off;


