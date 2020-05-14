#ifndef __CFG_PARSER_H
#define __CFG_PARSER_H

/* Includes */
#include <string>
#include <unordered_map>

/* Excepciones */
struct WorkerFileException : std::exception {
    char const *what();
};

/* Tipos */
typedef std::unordered_map<std::string, int> WorkerList;

/* Interfaz */
class ConfigParser {
   private:
    const std::string worker_filename;

   public:
    /* Recibe la ruta al archivo que contiene
    las cantidades de cada trabajador.*/
    explicit ConfigParser(const std::string worker_filename);
    ~ConfigParser();

    /* Devuelve una WorkerList de la forma
    {tipo_de_trabajador:cantidad} */
    WorkerList get_worker_list();
};

#endif
