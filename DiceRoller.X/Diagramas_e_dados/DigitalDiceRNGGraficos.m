
%Numero sorteado (de 1 a 20)
numbersArray  = 1:20;

%Quanto cada numero saiu em 20000 rolagems, seed = 1354
data1 = [1012  1006  994  1007  1005  1014  1010  1012  997  1012  991  997  997  994  996  989  994  979  1000  994];

%Quanto cada numero saiu em 20000 rolagems, seed = 5478
data2 = [1002  988  1012  986  1004  989  1009  1008  992  991  1004  989  990  992  1006  1012  1012  1010  1002  1002];

%Quanto cada numero saiu em 20000 rolagems, seed = 8700
data3 = [983  1001  995  1009  995  1009  990  989  1011  1004  1011  1015  1001  1001  1000  994  992  1007  998  995];

%Quanto cada numero saiu em 20000 rolagems, seed = 46892
data4 = [983  1006  998  996  1000  1010  996  990  1008  1000  1008  1009  1010  1000  998  991  991  1010  1001  995];

%Quanto cada numero saiu em 20000 rolagems, seed = 1000
data5 = [988  1005  998  1009  997  1007  985  985  1012  1002  1012  1017  1007  996  1000  995  995  1002  991  997];

%Quanto cada numero saiu em 20000 rolagems, seed = 0
data6 = [1001  990  1008  991  1009  993  1004  1007  996  997  1006  995  995  990  1009  994  1010  1002  1000  1003];

%plot dos graficos
plot(numbersArray, data1, numbersArray, data2, numbersArray, data3, numbersArray, data4, numbersArray, data5, numbersArray, data6)
axis([1 20 0 1200])
legend('seed 1354','seed 5478', 'seed 8700', 'seed 46892', 'seed 1000', 'seed 0')
xlabel('Numero sorteado no d20')
ylabel('Numero de vezes que saiu em 20000 rolagems')
