#include <iostream>
#include <limits>
#include "AVL.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Student pedirEstudiante() {
    Student s;
    cout << "ID: ";
    cin >> s.student_id;
    limpiarBuffer();
    cout << "Nombre completo: ";
    getline(cin, s.full_name);
    cout << "Carrera: ";
    getline(cin, s.career);
    cout << "Semestre: ";
    cin >> s.semester;
    cout << "GPA: ";
    cin >> s.gpa;
    cout << "Skill Score: ";
    cin >> s.skill_score;
    limpiarBuffer();
    return s;
}

int main() {
    AVLTree arbol;
    int opcion;

    do {
        cout << "\n--- Menu ---" << endl;
        cout << "Mynor Arias   9941-24-18934" << endl;
        cout << "1. Insertar estudiante" << endl;
        cout << "2. Mostrar ranking" << endl;
        cout << "3. Buscar por skill score" << endl;
        cout << "4. Estadisticas del arbol" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
        case 1:
            cout << "\nIngresa los datos del estudiante:" << endl;
            arbol.insert(pedirEstudiante());
            cout << "Estudiante agregado!" << endl;
            break;

        case 2:
            cout << "\nRanking academico:" << endl;
            arbol.printRanking();
            break;

        case 3: {
            int score;
            cout << "Skill score a buscar: ";
            cin >> score;
            limpiarBuffer();
            AVLNode* resultado = arbol.search(score);
            if (resultado != nullptr) {
                cout << "Encontrado:" << endl;
                cout << "  ID: " << resultado->data.student_id << endl;
                cout << "  Nombre: " << resultado->data.full_name << endl;
                cout << "  Carrera: " << resultado->data.career << endl;
                cout << "  Semestre: " << resultado->data.semester << endl;
                cout << "  GPA: " << resultado->data.gpa << endl;
                cout << "  Score: " << resultado->data.skill_score << endl;
            } else {
                cout << "No se encontro ningun estudiante con ese score." << endl;
            }
            break;
        }

        case 4:
            cout << "\nEstadisticas del arbol AVL:" << endl;
            cout << "Altura: " << arbol.getHeight() << endl;
            cout << "Balance de la raiz: " << arbol.getRootBalanceFactor() << endl;
            cout << "Total de estudiantes: " << arbol.getNodeCount() << endl;
            break;

        case 5:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << "Opcion no valida, intenta de nuevo." << endl;
        }

    } while (opcion != 5);

    return 0;
}
