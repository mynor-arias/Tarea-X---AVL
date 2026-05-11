#pragma once
#include "Student.h"

struct AVLNode {
    Student data;
    AVLNode* izquierda;
    AVLNode* derecha;
    int altura;

    AVLNode(const Student& s);
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const Student& s);
    AVLNode* search(int skill_score) const;
    void printRanking() const;

    int getHeight() const;
    int getRootBalanceFactor() const;
    int getNodeCount() const;

private:
    AVLNode* raiz;
    int totalNodos;

    int obtenerAltura(AVLNode* nodo) const;
    int obtenerBalance(AVLNode* nodo) const;
    AVLNode* rotarDerecha(AVLNode* y);
    AVLNode* rotarIzquierda(AVLNode* x);
    AVLNode* insertar(AVLNode* nodo, const Student& s);
    AVLNode* buscar(AVLNode* nodo, int skill_score) const;
    void mostrarRanking(AVLNode* nodo, int& pos) const;
    void destruir(AVLNode* nodo);
};
