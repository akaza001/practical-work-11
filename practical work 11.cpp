// -------------------------------
// № 1

// #include <iostream>

// int a[100][100];
// int dp[100][100];
// int path_i[200], path_j[200];

// int main() {
//     int n, m;
//     std::cin >> n >> m;
    
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             std::cin >> a[i][j];
//     int i = 0;
//     int j = 0;
//     std::cout << i << " " << j << std::endl;
//     while (i < n - 1 || j < m - 1){
//         if (a[i + 1][j] > a[i][j + 1]){
//             i++;
//             std::cout << i << " " << j << std::endl;
//         } else{
//             j++;
//             std::cout << i << " " << j << std::endl;
//         }
//     }
//     return 0;
// }


// -------------------------------
// № 2

// #include <iostream>
// #include <algorithm>
// using namespace std;

// int a[1005];
// int dp[1005][1005]; // dp[i][j] = минимальная максимальная разница, 
//                     // если распределить ПЕРВЫЕ i пирожков на j дней

// int main() {
//     int n, d;
//     cin >> n >> d;
    
//     for (int i = 0; i < n; i++)
//         cin >> a[i];
    
//     sort(a, a + n); // сортируем — выгоднее есть подряд идущие по калорийности
    
//     // БАЗА: если у нас всего 1 день, то все i пирожков идут в него.
//     // Разница = последний минус первый.
//     for (int i = 1; i <= n; i++)
//         dp[i][1] = a[i-1] - a[0];
    
//     // Теперь добавляем дни по одному: j = 2, 3, ..., d
//     for (int j = 2; j <= d; j++) {
//         for (int i = j; i <= n; i++) {
//             dp[i][j] = 1000000000; // пока что "бесконечность" (худший вариант)
            
//             // Перебираем: сколько пирожков (k) отдать ПЕРВЫМ j-1 дням.
//             // Тогда в последний (j-й) день пойдут пирожки с индекса k по i-1.
//             for (int k = j - 1; k < i; k++) {
//                 // Разница в j-м дне = a[i-1] - a[k] (последний минус первый в группе)
//                 // А максимальная разница среди всех дней = 
//                 //   либо то, что было в первых j-1 днях (dp[k][j-1]),
//                 //   либо разница в j-м дне (a[i-1] - a[k]).
//                 // Берём максимум из этих двух.
//                 int val = max(dp[k][j-1], a[i-1] - a[k]);
                
//                 // Ищем минимум по всем возможным k
//                 if (val < dp[i][j])
//                     dp[i][j] = val;
//             }
//         }
//     }
    
//     cout << dp[n][d] << endl; // ответ: все n пирожков на d дней
//     return 0;
// }



// -------------------------------
// № 3


// #include <iostream>
// using namespace std;

// int a[100];
// int count[100];      // сколько раз встречается каждая стоимость
// int unique[100];     // уникальные стоимости
// int unique_cnt = 0;  // количество уникальных стоимостей

// void sort_desc(int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - 1 - i; j++) {
//             if (a[j] < a[j+1]) {
//                 int temp = a[j];
//                 a[j] = a[j+1];
//                 a[j+1] = temp;
//             }
//         }
//     }
// }

// int main() {
//     int n, k, l;
//     cin >> n >> k >> l;
    
//     for (int i = 0; i < n; i++)
//         cin >> a[i];
    
//     sort_desc(n);  // сортируем по убыванию
    
//     // считаем, сколько раз встречается каждая стоимость
//     for (int i = 0; i < n; i++) {
//         bool found = false;
//         for (int j = 0; j < unique_cnt; j++) {
//             if (unique[j] == a[i]) {
//                 count[j]++;
//                 found = true;
//                 break;
//             }
//         }
//         if (!found) {
//             unique[unique_cnt] = a[i];
//             count[unique_cnt] = 1;
//             unique_cnt++;
//         }
//     }
    
//     // жадно берём самые дорогие растения
//     long long sum = 0;
//     int taken = 0;
    
//     for (int i = 0; i < unique_cnt && taken < k; i++) {
//         int take = count[i];
//         if (take > l)
//             take = l;  // не более L одинаковых
        
//         if (taken + take > k)
//             take = k - taken;  // чтобы не взять больше K
        
//         sum += (long long)take * unique[i];
//         taken += take;
//     }
    
//     cout << sum << endl;
    
//     return 0;
// }


// -------------------------------
// № 3

// #include <iostream>
// using namespace std;

// int n, m;
// char maze[100][100];
// bool visited[100][100];
// int max_pdf = -1;  // максимум собранных pdf, -1 значит выход не найден

// // направления: вниз, вверх, вправо, влево
// int dx[4] = {1, -1, 0, 0};
// int dy[4] = {0, 0, 1, -1};

// // DFS: ищем все пути от (x,y) до выхода E
// // collected - сколько pdf уже собрано на текущем пути
// void dfs(int x, int y, int collected) {
//     // если дошли до выхода - обновляем ответ
//     if (maze[x][y] == 'E') {
//         if (collected > max_pdf)
//             max_pdf = collected;
//         return;
//     }
    
//     // пробуем пойти в 4 стороны
//     for (int dir = 0; dir < 4; dir++) {
//         int nx = x + dx[dir];
//         int ny = y + dy[dir];
        
//         // проверяем границы
//         if (nx < 0 || nx >= n || ny < 0 || ny >= m)
//             continue;
        
//         // проверяем, что не стена и не посещали
//         if (maze[nx][ny] == '1' || visited[nx][ny])
//             continue;
        
//         // идём в новую клетку
//         visited[nx][ny] = true;
//         int add = (maze[nx][ny] == 'P') ? 1 : 0;
//         dfs(nx, ny, collected + add);
//         visited[nx][ny] = false;  // откатываем, чтобы искать другие пути
//     }
// }

// int main() {
//     cin >> n >> m;
    
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < m; j++)
//             cin >> maze[i][j];
    
//     // стартуем из верхнего левого угла
//     visited[0][0] = true;
//     int start_pdf = (maze[0][0] == 'P') ? 1 : 0;
//     dfs(0, 0, start_pdf);
    
//     if (max_pdf == -1)
//         cout << -1 << endl;  // выход не найден
//     else
//         cout << max_pdf << endl;
    
//     return 0;
// }