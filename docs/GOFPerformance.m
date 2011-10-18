source outputFile.m
Trials = [1:size(single_6)(2)]
Num_processors = 6;

plot(Trials, single_6, Trials, rows_6, Trials, col_6, Trials, full_6);
legend('Serial RT', 'Row RT', 'Column RT', 'Region RT');
title('Real-Time Comparison');
xlabel('Time (s)');
ylabel('Threading Models');
print -dpng 'rt_threading_compared.png';

plot(Trials, single_12, Trials, rows_12, Trials, col_12, Trials, full_12);
legend('Serial RT', 'Row RT', 'Column RT', 'Region RT');
title('Real-Time Comparison');
xlabel('Time (s)');
ylabel('Threading Models');
print -dpng 'rt_threading_compared12.png';

plot(Trials, single_24, Trials, rows_24, Trials, col_24, Trials, full_24);
legend('Serial RT', 'Row RT', 'Column RT', 'Region RT');
title('Real-Time Comparison');
xlabel('Time (s)');
ylabel('Threading Models');
print -dpng 'rt_threading_compared24.png';
