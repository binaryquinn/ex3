import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2
import Model 1.0

Dialog
{

    id:combatantDialog
    title:"Add a new combatant"

    property int longest: 0

    ListModel
    {
        id: abilityList
    Component.onCompleted:{

            var abilityStrings = myCons.allAbilities;
            var abilityIndex = 0;
            for(;abilityIndex< abilityStrings.length;abilityIndex++)
                  abilityList.append({"name":abilityStrings[abilityIndex], "stat":0});
        }
    }

    contentItem: AddCombatantDialogForm
    {

        id:form

        function clearFields()
        {
            nameText = "";
            soakText = hardnessText =  mpText = "";
            newWeaponText = newAccText = newAtkText = newDefText = newOverText = "";

            var index = 0;
            for(; index < attributeModel.count; index++)
            {
                attributeModel.set(index,{"stat":1});
            }
            for(; index < abilityList.count; index++)
                abilityList.set(index,{"stat":0});
            abilityCombo.currentIndex = 0;

            healthModel.set(0,{"hlCount":1});
            healthModel.set(1,{"hlCount":2});
            healthModel.set(2,{"hlCount":2});
            healthModel.set(3,{"hlCount":1});
            healthModel.set(4,{"hlCount":1});
        }
        abilityModel:abilityList

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
        okButton.onClicked:
        {
            var str = attributeModel.get(0).stat;
            var dex = attributeModel.get(1).stat;
            var sta = attributeModel.get(2).stat;
            var wit = attributeModel.get(3).stat;

            Tracker.add(nameText,str, dex, sta, wit );
            accept();


        }
       cancelButton.onClicked:
       {
           reject();
       }
    }

onVisibleChanged: if(!visible) form.clearFields();
}