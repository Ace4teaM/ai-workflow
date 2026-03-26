#ifndef SHARED_STACK_H
#define SHARED_STACK_H

#include <stdint.h>
#include <stddef.h>

// Définition des macros pour les usages
#define SYSTEM_RENDER  0x01
#define SYSTEM_DATA    0x02
#define SYSTEM_PHYSICS 0x03

#define TYPE_INT       0x01
#define TYPE_FLOAT     0x02
#define TYPE_BYTES     0x03

// Union pour stocker la valeur d'une propriété
typedef union {
    int32_t  as_int;
    float    as_float;
    uint8_t  as_bytes[4];
} PropertyValue;

// Structure d'une propriété (64 bits alignés)
typedef struct {
    uint32_t usage;   // 32 bits : système, type et usage (16 bits)
    PropertyValue value; // 32 bits : valeur (int, float ou bytes)
} Property;

// Structure d'un objet dans la pile partagée
typedef struct SharedObject {
    int32_t id;               // Identifiant unique de l'objet
    Property* properties;     // Pointeur vers la pile de propriétés
    size_t property_count;    // Nombre de propriétés
    struct SharedObject* next; // Pointeur vers l'objet suivant
} SharedObject;

// Structure de la pile mémoire partagée
typedef struct {
    SharedObject* objects;    // Liste des objets
    size_t object_count;      // Nombre d'objets
    size_t next_id;           // Prochain identifiant disponible
} SharedStack;

// Fonctions de gestion de la pile partagée

/**
 * @brief Initialise une pile mémoire partagée.
 *
 * @param stack Pointeur vers la pile à initialiser.
 */
void shared_stack_init(SharedStack* stack);

/**
 * @brief Libère toute la mémoire allouée pour la pile partagée.
 *
 * @param stack Pointeur vers la pile à libérer.
 */
void shared_stack_free(SharedStack* stack);

/**
 * @brief Crée un nouvel objet dans la pile partagée.
 *
 * @param stack Pointeur vers la pile.
 * @return Pointeur vers l'objet créé.
 */
SharedObject* shared_stack_create_object(SharedStack* stack);

/**
 * @brief Ajoute une propriété à un objet.
 *
 * @param object Pointeur vers l'objet.
 * @param usage Usage de la propriété (système, type et flags).
 * @param value Valeur de la propriété.
 */
void shared_stack_add_property(SharedObject* object, uint32_t usage, PropertyValue value);

/**
 * @brief Récupère une propriété d'un objet en fonction de son usage.
 *
 * @param object Pointeur vers l'objet.
 * @param usage Usage de la propriété à rechercher.
 * @return Pointeur vers la propriété ou NULL si non trouvée.
 */
Property* shared_stack_get_property(SharedObject* object, uint32_t usage);

/**
 * @brief Supprime une propriété d'un objet.
 *
 * @param object Pointeur vers l'objet.
 * @param usage Usage de la propriété à supprimer.
 */
void shared_stack_remove_property(SharedObject* object, uint32_t usage);

/**
 * @brief Supprime un objet de la pile partagée.
 *
 * @param stack Pointeur vers la pile.
 * @param id Identifiant de l'objet à supprimer.
 */
void shared_stack_remove_object(SharedStack* stack, int32_t id);

#endif // SHARED_STACK_H