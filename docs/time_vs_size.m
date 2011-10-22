load single.dat;
load col.dat;
load row.dat;
load full.dat;
count = col(:,1);

% data is a table of value. Each row is a run, with each column a repeat of that run.
function value_mean = separate_and_average(data)
    maxes = max(data', [], 1);
    mins = min(data', [], 1);
    data = setdiff(data', maxes, 'rows')';
    data = setdiff(data', mins, 'rows')';
    value_mean = mean(data');
endfunction

single = single(:, 2:end);
sin_avg = separate_and_average(single)/1000;

col = col(:, 2:end);
col_avg = separate_and_average(col)/1000;

row = row(:, 2:end);
row_avg = separate_and_average(row)/1000;

full = full(:, 2:end);
full_avg = separate_and_average(full)/1000;

plot(count, col_avg, count, row_avg, count, full_avg, count, sin_avg);
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition', 'Serial')
xlabel('Grid Size (n by n)')
ylabel('Time (s)')
print -dpng 'comparison.png';

%Caulculate Speedups.
colspeedup = sin_avg./col_avg;
rowspeedup = sin_avg./row_avg;
fullspeedup = sin_avg./full_avg;
normalized = sin_avg./sin_avg;
plot(count, colspeedup, count, rowspeedup, count, fullspeedup, count, normalized);
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition', 'Serial');
xlabel('Grid Size (n by n)');
ylabel('Speed-Up');
print -dpng 'speedup.png'

%Calculate efficiency
col_eff = sin_avg./(col_avg*6)*100;
row_eff = sin_avg./(row_avg*6)*100;
full_eff = sin_avg./(full_avg*6)*100;
plot(count, col_eff, count, row_eff, count, full_eff);
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition');
xlabel('Grid Size (n by n)');
ylabel('Efficiency (%)');
print -dpng 'efficiency.png';


%fit all the data to make prettier graphs

function [x, y] = polyfit_and_resample(xdata, ydata, samples)
    p = polyfit(xdata, ydata', 2);
    x = linspace(min(xdata), max(xdata), samples);
    y = polyval(p,x);
endfunction


[sx,sy] = polyfit_and_resample(count, sin_avg, 101);
[rx,ry] = polyfit_and_resample(count, row_avg, 101);
[cx,cy] = polyfit_and_resample(count, col_avg, 101);
[fx,fy] = polyfit_and_resample(count, full_avg, 101);
plot(cx, cy, rx,ry, fx,fy, sx,sy)
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition', 'Serial')
xlabel('Grid Size (n by n)')
ylabel('Time (s)')
print -dpng 'fitted-comparison.png'

[sx,sy] = polyfit_and_resample(count, normalized, 101);
[rx,ry] = polyfit_and_resample(count, rowspeedup, 101);
[cx,cy] = polyfit_and_resample(count, colspeedup, 101);
[fx,fy] = polyfit_and_resample(count, fullspeedup, 101);
plot(cx, cy, rx,ry, fx,fy, sx,sy)
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition', 'Serial')
xlabel('Grid Size (n by n)')
ylabel('Speed-up')
print -dpng 'fitted-speedup.png'


[rx,ry] = polyfit_and_resample(count, row_eff, 101);
[cx,cy] = polyfit_and_resample(count, col_eff, 101);
[fx,fy] = polyfit_and_resample(count, full_eff, 101);
plot(cx, cy, rx,ry, fx,fy)
legend('Column Decomposition', 'Row Decomposition', 'Full Decomposition')
xlabel('Grid Size (n by n)')
ylabel('Efficiency (%)')
print -dpng 'fitted-efficiency.png'





