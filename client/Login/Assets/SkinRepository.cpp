#include "SkinRepository.h"
#include "server/Skin.h"
#include "server/Team.h"

QVector<SkinInfo> SkinRepository::getSkinsForTeam(uint8_t teamId) {
    if (teamId == Team::TERRORISTS) {
        return {
                {"Phoenix", ":/skins/phoenix.png", "Login/Assets/Skins/Phoenix.png", Skin::PHOENIX},
                {"L337 Krew", ":/skins/l337.png", "Login/Assets/Skins/L337 Krew.png", Skin::L337_KREW},
                {"Arctic Avenger", ":/skins/arctic.png", "Login/Assets/Skins/Artic Avenger.png", Skin::ARCTIC_AVENGER},
                {"Guerrilla", ":/skins/guerrilla.png", "Login/Assets/Skins/Guerrilla.png", Skin::GUERRILLA}
        };
    } else if (teamId == Team::COUNTER_TERRORISTS) {
        return {
                {"SEAL Force", ":/skins/sealforce.png", "Login/Assets/Skins/SealForce.png", Skin::SEAL_FORCE},
                {"German GSG9", ":/skins/gsg9.png", "Login/Assets/Skins/German GSG-9.png", Skin::GERMAN_GSG9},
                {"UK SAS", ":/skins/sas.png", "Login/Assets/Skins/UK SAS.png", Skin::UK_SAS},
                {"French GIGN", ":/skins/gign.png", "Login/Assets/Skins/French GIGN.png", Skin::FRENCH_GIGN}
        };
    }

    return {};
}
