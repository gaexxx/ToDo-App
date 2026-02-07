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
    std::vector<std::unique_ptr<Activity>>
    load(const QString& path) const;

    // salva tutte le attività nel file JSON (ownership)
    void save(const QString& path,
        const std::vector<std::unique_ptr<Activity>>& activities) const;

    // salva solo attivita' visibili (non owning)
    void save(const QString& path,
        const std::vector<Activity*>& activities) const;

    // importa attivita'                  
    std::vector<std::unique_ptr<Activity>> 
    loadFromFile(const QString& path) const;
};

} 

#endif
