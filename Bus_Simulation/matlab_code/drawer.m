% This file is used to show the difference between original version and optimization version of the system

y = [251.639 82.3545; 234.784 131.681; 237.646 101.726; 271.22 152.095; 295.681 140.558; 340.233 91.8254; 305.957 76.141; 280.748 92.5077; 249.142 76.5169; 238.844 108.545; 274.896 145.739; 269.996 100.543; 317.142 103.411; 323.256 70.3247; 282.88 88.5326];
b = bar(y);
grid on;
ch = get(b, 'children');
set(gca, 'XTickLabel', {'Stop 0','Stop 1','Stop 2','Stop 3', 'Stop 4','Stop 5', 'Stop 6','Stop 7', 'Stop 8','Stop 9', 'Stop 10','Stop 11', 'Stop 12','Stop 13', 'Stop 14'})
legend('Buses Not Keep distance uniform','Buses Keep distance uniform');
%set(ch,'FaceVertexCData',[1 0 1;0 0 0;]);
xlabel(' stop number ');
ylabel(' Average Waiting People Number');