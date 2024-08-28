/*
Autor: Sander Sierra
Funciones para la validación de datos haciendo uso de plantillas para evitar
repetición de codigo y amplio rango de tipo de datos solo numericos. Se
recomienda solo usar tipos de datos numericos.
*/

/*
Ejemplo de uso:

cout << "Ingrese un número entero:\n";
int input_opt = input_func<long int>();
cout << input_opt;

cout << "\nIngrese un número positivo:\n";

int input_pos = input_func<unsigned long long int>();
cout << input_pos;

cout << "\nIngrese un número flotante:\n";
double input_f_opt = input_func<long double>();

cout << input_f_opt;
*/
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <string>

using namespace std;

// Quita los espacios al final de un string pasado por referencia
inline void remove_final_spaces(string &targetString) {
  int no_space_index = targetString.length() - 1;

  // Si hay un espacio de derecha a izquierda el indice se mueve a la izquierda
  while (no_space_index >= 0 && targetString[no_space_index] == ' ') {
    no_space_index--;
  }

  // Elimina desde la ultima posicion + 1 hasta el final
  targetString.erase(no_space_index + 1);
}

// Quita los espacios al comienzo de un string pasado por referencia
inline void remove_initial_spaces(string &targetString) {
  int no_space_index = 0;

  // Si hay un espacio de izquierda a derecha el indice se mueve a la derecha
  while (no_space_index >= 0 && targetString[no_space_index] == ' ') {
    no_space_index++;
  }

  // Elimina desde la posicion 0 hasta el ultimo espacio (indice)
  targetString.erase(0, no_space_index);
}

// Recibe un string y un tipo de dato cualquiera como dummy.
// La función está hecha para validar tipos de datos numericos como:
// - float, int. Incluso con modificadores como unsigned.
// Verdadero si es valido, sino falso.
template <typename T> bool validar(const string &refString, T dummy) {
  bool existePunto = false; // Para prohibir que hayan mas de dos puntos
  int indx_resp = -1;       // Para que empiece desde 0

  for (const char letter : refString) {
    indx_resp++;

    if (letter == '-') {
      if (indx_resp > 0) {
        cout << "[Error] El signo '-' solo puede ir al comienzo y una única "
                "vez.\n";
        return false;
      }

      if (refString.length() == 1) {
        cout << "[Error] El signo '-' debe estar acompañado por un numeros a "
                "la derecha.\n";
        return false;
      }

      // is_unsigned recibe un tipo de dato y verifica que sea unsigned
      // para usarlo en un if se debe añadir ::value que seria bool
      if (is_unsigned<T>::value) {
        cout << "[Error] No se permiten números negativos.\n";
        return false;
      }

      continue; // No se debe seguir porque ya se sabe que la letra es '-'
    }

    if (letter == '.') {
      // is_floating_point recibe un tipo de dato y verifica que sea
      // de tipo flotante, es decir, double o float.
      if (!is_floating_point<T>::value) {
        cout << "[Error] No se permiten puntos.\n";
        return false;
      }

      if (indx_resp == 0) {
        cout << "[Error] El punto no puede ir al comienzo.\n";
        return false;
      }
      if (indx_resp == refString.length() - 1) {
        cout << "[Error] El punto no puede ir al final.\n";
        return false;
      }
      if (existePunto) {
        cout << "[Error] No puede haber más de un punto.\n";
        return false;
      }

      existePunto = true; // El punto es valido.

      continue;
    }

    // isdigit recibe un char y valida si es un digito del 0 al 9
    if (!isdigit(letter)) {
      cout << "[Error] Solo se permiten números.\n";
      return false;
    }
  }

  return true;
}

// No recibe argumentos.
// La función pide una entrada por parte del usuario y lo valida. Devuelve la
// entrada del usuario si es valida, sino intenta infinitamente.
// Uso de la función: tipo_dato var = input_func<tipo_dato>();
template <typename T> T input_func() {
  string input_user;
  T output;

  do {
    cout << ">> ";
    getline(cin >> ws, input_user);
    remove_final_spaces(input_user);

    // Se usa la funcion validar, output es pasado como argumento pero su valor
    // no se modifica, se pasa para diferenciar el tipo de dato
    if (!validar(input_user, output))
      continue;

    // Dependiendo del tipo de dato se usa una función distinta para transformar
    // de string a ese tipo de dato. Se usa la función que permita más bytes. Se
    // usa un try-catch para evitar que el codigo se rompa. En cambio, muestra
    // el posible error.
    try {
      if (is_floating_point<T>::value) {
        output = stold(input_user); // string to long double

      } else if (is_integral<T>::value) {
        // is_integral verifica si el tipo está dentro de un conjunto que
        // incluye tipos de datos numericos
        if (is_unsigned<T>::value) {
          output = stoull(input_user); // string to unsigned long long
        } else
          output = stoll(input_user); // sttring to long long
      }
      break;
    } catch (const std::out_of_range &) {
      cout << "[Error] El valor está fuera del rango permitido para el tipo de "
              "datos.\n";
    } catch (...) {
      // Un error cualquiera
      cout << "[Error] Sucedió un error al convertir al tipo. Inténtelo de "
              "nuevo.\n";
    }
  } while (true);

  return output;
}

template <typename T> T input_between(T minimo, T maximo) {
  T num;

  do {
    num = input_func<T>();

    if (num < minimo || num > maximo)
      cout << "Ingrese un numero entre " << minimo << " y " << maximo
           << ". Incluidos.\n";
    else
      break;
  } while (true);

  return num;
}

#endif