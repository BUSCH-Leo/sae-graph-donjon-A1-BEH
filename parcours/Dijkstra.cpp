#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure pour représenter un nœud dans le graphe
struct Node {
    int x, y, distance, enemies;

    Node(int _x, int _y, int _distance, int _enemies) : x(_x), y(_y), distance(_distance), enemies(_enemies) {}

    bool operator<(const Node& other) const {
        if (enemies == other.enemies)
            return distance > other.distance;
        return enemies > other.enemies;
    }
};

// Fonction pour vérifier si les coordonnées sont valides dans la matrice
bool isValid(int x, int y, int taille) {
    return x >= 0 && x < taille && y >= 0 && y < taille;
}

vector<pair<int, int>> Dijkstra(vector<vector<bool>>& matrice_adjacence, int taille, int departX, int departY, int arriveeX, int arriveeY, loot** LootsMatrix) {
    vector<vector<int>> distance(taille, vector<int>(taille, INT_MAX));
    vector<vector<int>> enemies(taille, vector<int>(taille, INT_MAX));
    priority_queue<Node> pq;

    distance[departX][departY] = 0;
    enemies[departX][departY] = 0;
    pq.push(Node(departX, departY, 0, 0));

    vector<vector<pair<int, int>>> previous(taille, vector<pair<int, int>>(taille, {-1, -1}));

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.x == arriveeX && curr.y == arriveeY)
            break;

        for (int i = 0; i < 4; ++i) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];
            if (isValid(newX, newY, taille) && matrice_adjacence[curr.x * taille + curr.y][newX * taille + newY]) {
                int newEnemies = curr.enemies + (LootsMatrix[newX][newY].type == "Ennemi" ? 1 : 0);
                if ((newEnemies < enemies[newX][newY]) || (newEnemies == enemies[newX][newY] && distance[curr.x][curr.y] + 1 < distance[newX][newY])) {
                    distance[newX][newY] = distance[curr.x][curr.y] + 1;
                    enemies[newX][newY] = newEnemies;
                    pq.push(Node(newX, newY, distance[newX][newY], newEnemies));
                    previous[newX][newY] = {curr.x, curr.y};
                }
            }
        }
    }

    vector<pair<int, int>> chemin;
    int x = arriveeX, y = arriveeY;
    while (x != -1 && y != -1 && x < taille && y < taille) {
        chemin.push_back({y, x});
        int tempX = previous[x][y].first;
        int tempY = previous[x][y].second;
        x = tempX;
        y = tempY;
    }

    cout << "\n     - Distance minimale : " << distance[arriveeX][arriveeY] << endl;
    cout << "     - Nombre d'ennemis rencontrés minimal : " << enemies[arriveeX][arriveeY] << "\n" << endl;

    return chemin;
}
