#include "AVL.h"
#include <iostream>
#include <algorithm>
using namespace std;

AVLNode::AVLNode(const Student& s) {
    data = s;
    izquierda = nullptr;
    derecha = nullptr;
    altura = 1;
}

AVLTree::AVLTree() {
    raiz = nullptr;
    totalNodos = 0;
}

AVLTree::~AVLTree() {
    destruir(raiz);
}

void AVLTree::destruir(AVLNode* nodo) {
    if (nodo == nullptr) return;
    destruir(nodo->izquierda);
    destruir(nodo->derecha);
    delete nodo;
}


int AVLTree::obtenerAltura(AVLNode* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}


int AVLTree::obtenerBalance(AVLNode* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    return obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha);
}


AVLNode* AVLTree::rotarDerecha(AVLNode* y) {
    AVLNode* x = y->izquierda;
    AVLNode* temp = x->derecha;

    x->derecha = y;
    y->izquierda = temp;

    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

    return x;
}


AVLNode* AVLTree::rotarIzquierda(AVLNode* x) {
    AVLNode* y = x->derecha;
    AVLNode* temp = y->izquierda;

    y->izquierda = x;
    x->derecha = temp;

    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

    return y;
}

// compara dos estudiantes por skill_score, desempata por student_id
static bool menorQue(const Student& a, const Student& b) {
    if (a.skill_score != b.skill_score)
        return a.skill_score < b.skill_score;
    return a.student_id < b.student_id;
}

AVLNode* AVLTree::insertar(AVLNode* nodo, const Student& s) {
    if (nodo == nullptr) {
        return new AVLNode(s);
    }

    if (menorQue(s, nodo->data)) {
        nodo->izquierda = insertar(nodo->izquierda, s);
    } else {
        nodo->derecha = insertar(nodo->derecha, s);
    }

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

    int balance = obtenerBalance(nodo);

    // Caso LL
    if (balance > 1 && menorQue(s, nodo->izquierda->data)) {
        return rotarDerecha(nodo);
    }

    // Caso RR
    if (balance < -1 && !menorQue(s, nodo->derecha->data)) {
        return rotarIzquierda(nodo);
    }

    // Caso LR
    if (balance > 1 && !menorQue(s, nodo->izquierda->data)) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    // Caso RL
    if (balance < -1 && menorQue(s, nodo->derecha->data)) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void AVLTree::insert(const Student& s) {
    raiz = insertar(raiz, s);
    totalNodos++;
}

AVLNode* AVLTree::buscar(AVLNode* nodo, int skill_score) const {
    if (nodo == nullptr) return nullptr;
    if (skill_score == nodo->data.skill_score) return nodo;
    if (skill_score < nodo->data.skill_score) return buscar(nodo->izquierda, skill_score);
    return buscar(nodo->derecha, skill_score);
}

AVLNode* AVLTree::search(int skill_score) const {
    return buscar(raiz, skill_score);
}

// recorre de mayor a menor para el ranking
void AVLTree::mostrarRanking(AVLNode* nodo, int& pos) const {
    if (nodo == nullptr) return;
    mostrarRanking(nodo->derecha, pos);
    cout << pos << ". " << nodo->data.full_name << " - Score: " << nodo->data.skill_score << endl;
    pos++;
    mostrarRanking(nodo->izquierda, pos);
}

void AVLTree::printRanking() const {
    if (raiz == nullptr) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }
    int pos = 1;
    mostrarRanking(raiz, pos);
}

int AVLTree::getHeight() const {
    return obtenerAltura(raiz);
}

int AVLTree::getRootBalanceFactor() const {
    return obtenerBalance(raiz);
}

int AVLTree::getNodeCount() const {
    return totalNodos;
}
