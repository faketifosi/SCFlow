% OPTICS demo

x = [randn(30,2)*.4;randn(40,2)*.5+ones(40,1)*[4 4]];

[RD,CD,order] = optics(x,4);

figure(1);
plot(x(:,1),x(:,2),'go');
axis off;

figure(2);
bar(RD);
