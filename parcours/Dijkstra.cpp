#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure pour représenter un nœud dans le graphe
struct Node {
    int x, y, distance;

    Node(int _x, int _y, int _distance) : x(_x), y(_y), distance(_distance) {}

    // Surcharge de l'opérateur < pour utiliser dans la file de priorité
    bool operator<(const Node& other) const {
        return distance > other.distance;
    }
};

// Fonction pour vérifier si les coordonnées sont valides dans la matrice
bool isValid(int x, int y, int taille) {
    return x >= 0 && x < taille && y >= 0 && y < taille;
}

vector<pair<int, int>> Dijkstra(vector<vector<bool>>& matrice_adjacence, int taille, int departX, int departY, int arriveeX, int arriveeY) {
    // Tableau pour stocker les distances minimales
    vector<vector<int>> distance(taille, vector<int>(taille, INT_MAX));
    // File de priorité pour choisir le nœud avec la distance minimale
    priority_queue<Node> pq;

    // Distance du départ à lui-même est 0
    distance[departX][departY] = 0;
    // Ajouter le départ à la file de priorité
    pq.push(Node(departX, departY, 0));

    // Tableau pour stocker les coordonnées précédentes pour reconstruire le chemin
    vector<vector<pair<int, int>>> previous(taille, vector<pair<int, int>>(taille, {-1, -1}));

    // Déplacements possibles dans toutes les directions (haut, bas, gauche, droite)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        // Si nous atteignons le nœud d'arrivée, nous pouvons arrêter
        if (curr.x == arriveeX && curr.y == arriveeY)
            break;

        // Parcourir les nœuds voisins
        for (int i = 0; i < 4; ++i) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];
            // Vérifier si les nouvelles coordonnées sont valides
            if (isValid(newX, newY, taille) && matrice_adjacence[curr.x * taille + curr.y][newX * taille + newY]) {
                // Mettre à jour la distance si elle est plus petite
                if (distance[curr.x][curr.y] + 1 < distance[newX][newY]) {
                    distance[newX][newY] = distance[curr.x][curr.y] + 1;
                    pq.push(Node(newX, newY, distance[newX][newY]));
                    // Mettre à jour les coordonnées précédentes uniquement si une nouvelle distance minimale est trouvée
                    previous[newX][newY] = {curr.x, curr.y};

                } else if (distance[curr.x][curr.y] + 1 == distance[newX][newY] && previous[newX][newY] == make_pair(-1, -1)) {
                    // Si la distance est la même mais les coordonnées précédentes n'ont pas encore été mises à jour, mettez à jour maintenant
                    previous[newX][newY] = {curr.x, curr.y};
                }
            }
        }
    }

    // Reconstruire le chemin à partir des coordonnées précédentes
    vector<pair<int, int>> chemin;
    int x = arriveeX, y = arriveeY;
    int distanceParcourue = 0; // Initialisation du compteur de distance
    while (x != -1 && y != -1 && x < taille && y < taille) {
        chemin.push_back({y, x});
        int tempX = previous[x][y].first;
        int tempY = previous[x][y].second;
        x = tempX;
        y = tempY;
        distanceParcourue++; // Incrémenter le compteur de distance
    }

    // Afficher le chemin parcouru
    cout << "Chemin parcouru : ";
    for (int i = chemin.size() - 1; i >= 0; --i) {
        cout << "(" << chemin[i].first << "," << chemin[i].second << ")";
        if (i != 0) {
            cout << " -> ";
        }
    }
    cout << endl;

    // Afficher la distance minimale entre le départ et l'arrivée
    cout << "Distance minimale : " << distanceParcourue << endl;

    // Retourner le chemin parcouru
    return chemin;
}