#ifndef _EDITOR_LAYERMANAGER_HPP__
#define _EDITOR_LAYERMANAGER_HPP__

/**
 * @file LayerManager.hpp
 * @brief Gestion des calques (ajout/suppression, ordre, visibilité).
 *
 * Structure simple pour gérer plusieurs calques de tuiles.
 */

#include <vector>
#include <string>

namespace Editor {

/**
 * @struct Layer
 * @brief Représente un calque basique.
 */
struct Layer {
    std::string name;
    bool visible = true;
    bool locked = false;
    std::vector<int> data;
};

/**
 * @class LayerManager
 * @brief Gestionnaire de calques.
 */
class LayerManager
{
public:
    LayerManager();
    ~LayerManager();

    void addLayer(const std::string& name);
    void removeLayer(int index);
    void moveLayerUp(int index);
    void moveLayerDown(int index);

    void render();

private:
    std::vector<Layer> m_layers;
    int m_selected;
};

} // namespace Editor

#endif
