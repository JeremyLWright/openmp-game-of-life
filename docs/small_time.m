load sm_single.dat;
load sm_col.dat;
load sm_row.dat;
load sm_full.dat;

count = sm_single(:,1);
times = sm_single(:, 2:end);
avg = mean(times')/1000;

col = sm_col(:, 2:end);
col_avg = mean(col')/1000;

row = sm_row(:, 2:end);
row_avg = mean(row')/1000;

full = sm_full(:, 2:end);
full_avg = mean(full')/1000;


plot(count, avg, count, col_avg, count, row_avg, count, full_avg);
legend('Single Threaded', 'Column Decomposition', 'Row Decomposition', 'Full Decomposition')
xlabel('Grid Size (n by n)')
ylabel('Time (s)')
title('Threaded Comparison')
print -dpng 'zoom_comparison.png'

