load single.dat;
count = single(:,1);
times = single(:, 2:end);
t = mean(times')/1000;
plot(count, t);
legend('Single Threaded')
xlabel('Grid Size (n by n)')
ylabel('Time (s)')
title('Single Threaded')
print -dpng 'single.png'

