
% This file is used as plot the buses location 



[a1,a2] = textread('/Users/sumomoxiao/Desktop/CS520_Optimization/CS520_HomeWork2_BUSSIMULATION/Bus_number_one.txt', '%n%n');
[a3,a4] = textread('/Users/sumomoxiao/Desktop/CS520_Optimization/CS520_HomeWork2_BUSSIMULATION/Bus_number_two.txt', '%n%n');
[a5,a6] = textread('/Users/sumomoxiao/Desktop/CS520_Optimization/CS520_HomeWork2_BUSSIMULATION/Bus_number_three.txt', '%n%n');
[a7,a8] = textread('/Users/sumomoxiao/Desktop/CS520_Optimization/CS520_HomeWork2_BUSSIMULATION/Bus_number_four.txt', '%n%n');
[a9,a10] = textread('/Users/sumomoxiao/Desktop/CS520_Optimization/CS520_HomeWork2_BUSSIMULATION/Bus_number_five.txt', '%n%n');

len1 = length(a1)
len2 = length(a3)
len3 = length(a5)
len4 = length(a7)
len5 = length(a9)
 
 for i = 1:len1,
     plot(a1(i),a2(i),'r*');
     hold on;
 end
 
 for i = 1:len2,
     plot(a3(i),a4(i),'b*');
     hold on;
 end
 
 for i = 1:len3,
     plot(a5(i),a6(i),'gp');
     hold on;
 end
 
 for i = 1:len4,
     plot(a7(i),a8(i),'yh');
     hold on;
 end
 
 for i = 1:len5,
     plot(a9(i),a10(i),'ko');
     hold on;
 end
 
 title('Bus location plot');
 xlabel('time (0 - 28800)');
 ylabel('stop  (0 - 14) ');
