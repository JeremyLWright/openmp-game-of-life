load single.dat;
load col.dat;
load row.dat;
load full.dat;

count = single(:,1);
times = single(:, 2:end);
avg = mean(times')/1000;

col = col(:, 2:end);
col_avg = mean(col')/1000;

row = row(:, 2:end);
row_avg = mean(row')/1000;

full = full(:, 2:end);
full_avg = mean(full')/1000;

plot(count, avg, count, col_avg, count, row_avg, count, full_avg);
legend('Single Threaded', 'Column Decomposition', 'Row Decomposition', 'Full Decomposition')
xlabel('Grid Size (n by n)')
ylabel('Time (s)')
title('Threaded Comparison')
print -dpng 'comparison.png'

