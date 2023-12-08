#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col;
} Point;

int bfs(int N, int M, int maze[N][M]) {
    int dr[] = {-1, 0, 1, 0}; // 상하좌우 방향
    int dc[] = {0, 1, 0, -1};

    // 시작점과 도착점
    Point start = {0, 0};
    Point end = {N - 1, M - 1};

    // 방문 여부와 거리를 저장하는 배열
    int visited[N][M];
    int distance[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            visited[i][j] = 0;
            distance[i][j] = 0;
        }
    }

    visited[start.row][start.col] = 1;

    // BFS 큐
    Point queue[N * M];
    int front = 0, rear = 0;

    queue[rear++] = start;

    while (front < rear) {
        Point current = queue[front++];

        // 현재 위치에서 상하좌우로 이동
        for (int i = 0; i < 4; i++) {
            int nr = current.row + dr[i];
            int nc = current.col + dc[i];

            // 미로 범위를 벗어난 경우 무시
            if (nr < 0 || nr >= N || nc < 0 || nc >= M)
                continue;

            // 이동할 수 있는 칸이면서 아직 방문하지 않은 경우
            if (maze[nr][nc] == 1 && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                distance[nr][nc] = distance[current.row][current.col] + 1;
                queue[rear++] = (Point){nr, nc};
            }
        }
    }

    return distance[end.row][end.col] + 1; // 시작점도 포함하여 거리 반환
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int maze[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1d", &maze[i][j]);
        }
    }

    int result = bfs(N, M, maze);

    printf("%d\n", result);

    return 0;
}
