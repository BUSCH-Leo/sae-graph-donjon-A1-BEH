#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure pour représenter un nœud dans le graphe
struct Node {
    int x, y, distance, enemies;

    Node(int _x, int _y, int _distance, int _enemies) : x(_x), y(_y), distance(_distance), enemies(_enemies) {}

    // Surcharge de l'opérateur < pour utiliser dans la file de priorité
    bool operator<(const Node& other) const {
        if (enemies == other.enemies)
            return distance > other.distance; // Priorité à la distance si le nombre d'ennemis est égal
        return enemies > other.enemies; // Priorité au nombre d'ennemis
    }
};

// Fonction pour vérifier si les coordonnées sont valides dans la matrice
bool isValid(int x, int y, int taille) {
    return x >= 0 && x < taille && y >= 0 && y < taille;
}

vector<pair<int, int>> Dijkstra(vector<vector<bool>>& matrice_adjacence, int taille, int departX, int departY, int arriveeX, int arriveeY, loot** LootsMatrix) {
    // Tableau pour stocker les distances minimales
    vector<vector<int>> distance(taille, vector<int>(taille, INT_MAX));
    // Tableau pour stocker le nombre d'ennemis minimaux
    vector<vector<int>> enemies(taille, vector<int>(taille, INT_MAX));
    // File de priorité pour choisir le nœud avec la distance minimale
    priority_queue<Node> pq;

    // Distance et ennemis du départ à lui-même est 0
    distance[departX][departY] = 0;
    enemies[departX][departY] = 0;
    // Ajouter le départ à la file de priorité
    pq.push(Node(departX, departY, 0, 0));

    // Tableau pour stocker les coordonnées précédentes pour reconstruire le chemin
    vector<vector<pair<int, int>>> previous(taille, vector<pair<int, int>>(taille, {-1, -1}));

    // Déplacements possibles dans toutes les directions (haut, bas, gauche, droite)
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

    // Reconstruire le chemin à partir des coordonnées précédentes
    vector<pair<int, int>> chemin;
    int x = arriveeX, y = arriveeY;
    while (x != -1 && y != -1 && x < taille && y < taille) {
        chemin.push_back({y, x});
        int tempX = previous[x][y].first;
        int tempY = previous[x][y].second;
        x = tempX;
        y = tempY;
    }

    // Afficher la distance minimale et le nombre d'ennemis entre le départ et l'arrivée
    cout << "\n     - Distance minimale : " << distance[arriveeX][arriveeY] << endl;
    cout << "     - Nombre d'ennemis rencontrés : " << enemies[arriveeX][arriveeY] << "\n" << endl;

    // Retourner le chemin parcouru
    return chemin;
}
