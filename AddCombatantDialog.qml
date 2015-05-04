import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2
import Model 1.0

Dialog{
    id:combatantDialog
    title:"Add a new combatant"
    standardButtons: StandardButton.Ok|StandardButton.Cancel


    AddCombatantDialogForm {

        addWeaponButton.onClicked:
        {
            var name = newWeaponText.trim();

            if(name.length > 0)
            {
                var acc = (newAccText !== "")? Number(newAccText) : 0;
                var atk = (newAtkText !== "")? Number(newAtkText) : 0;
                var def = (newDefText !== "")? Number(newDefText) : 0;
                var over = (newOverText !== "")? Number(newOverText) : 0;

                weaponsModel.append({"name":name,"acc":acc, "atk":atk, "def":def, "over":over});
                newWeaponText = newAccText = newAtkText = newDefText = newOverText = "";

            }
        }
    }
}