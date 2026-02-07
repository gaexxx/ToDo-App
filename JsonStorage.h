#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include <vector>
#include <memory>
#include <QString>
#include "Activity.h"

namespace Todo {

class Activity;

class JsonStorage {
public:
    // carica tutte le attività dal file JSON
    static std::vector<std::unique_ptr<Activity>>
    load(const QString& path);

    // salva tutte le attività nel file JSON
    static void save(const QString& path,
            const std::vector<std::unique_ptr<Activity>>& activities);

    // salva solo attivita' visibili
    void save(const QString& path,
            const std::vector<Activity*>& activities) const;

    // importa attivita'                  
    static std::vector<std::unique_ptr<Activity>> loadFromFile(const QString& path);
};

} 

#endif
