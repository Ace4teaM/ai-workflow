#include "shared_stack.h"
#include <stdlib.h>
#include <string.h>

void shared_stack_init(SharedStack* stack) {
    if (stack == NULL) return;
    stack->objects = NULL;
    stack->object_count = 0;
    stack->next_id = 1; // Les IDs commencent à 1
}

void shared_stack_free(SharedStack* stack) {
    if (stack == NULL) return;

    SharedObject* current = stack->objects;
    while (current != NULL) {
        SharedObject* next = current->next;
        free(current->properties);
        free(current);
        current = next;
    }
    stack->objects = NULL;
    stack->object_count = 0;
    stack->next_id = 1;
}

SharedObject* shared_stack_create_object(SharedStack* stack) {
    if (stack == NULL) return NULL;

    SharedObject* new_object = (SharedObject*)malloc(sizeof(SharedObject));
    if (new_object == NULL) return NULL;

    new_object->id = stack->next_id++;
    new_object->properties = NULL;
    new_object->property_count = 0;
    new_object->next = stack->objects;
    stack->objects = new_object;
    stack->object_count++;
    return new_object;
}

void shared_stack_add_property(SharedObject* object, uint32_t usage, PropertyValue value) {
    if (object == NULL) return;

    Property* new_properties = (Property*)realloc(object->properties, (object->property_count + 1) * sizeof(Property));
    if (new_properties == NULL) return;

    object->properties = new_properties;
    object->properties[object->property_count].usage = usage;
    object->properties[object->property_count].value = value;
    object->property_count++;
}

Property* shared_stack_get_property(SharedObject* object, uint32_t usage) {
    if (object == NULL) return NULL;

    for (size_t i = 0; i < object->property_count; i++) {
        if (object->properties[i].usage == usage) {
            return &object->properties[i];
        }
    }
    return NULL;
}

void shared_stack_remove_property(SharedObject* object, uint32_t usage) {
    if (object == NULL) return;

    for (size_t i = 0; i < object->property_count; i++) {
        if (object->properties[i].usage == usage) {
            // Décaler les propriétés suivantes
            for (size_t j = i; j < object->property_count - 1; j++) {
                object->properties[j] = object->properties[j + 1];
            }
            object->property_count--;
            Property* new_properties = (Property*)realloc(object->properties, object->property_count * sizeof(Property));
            if (new_properties != NULL || object->property_count == 0) {
                object->properties = new_properties;
            }
            return;
        }
    }
}

void shared_stack_remove_object(SharedStack* stack, int32_t id) {
    if (stack == NULL || stack->objects == NULL) return;

    SharedObject* current = stack->objects;
    SharedObject* previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                stack->objects = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->properties);
            free(current);
            stack->object_count--;
            return;
        }
        previous = current;
        current = current->next;
    }
}