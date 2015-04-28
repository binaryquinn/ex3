import QtQuick 2.4

AddCombatantDialogForm {

    function addWeapon( name, acc, atk, def, over, weaponModel)
    {
        acc = acc.toInt();
        if(name.trim().length > 0)
            weaponModel.append({"name":name,"acc":(!!acc)?acc:0, "atk":(!!atk)?atk:0, "def":(!!def)?def:0, "over":(!!over)?over:0});
    }

    addWeaponButton.onClicked:
    {
        var name = newWeaponField.text.trim();
        var acc = (newAccField.text.length>0)?newAccField.text.valueOf():0;
        var atk = (newAtkField.text.length>0)?newAtkField.text.valueOf():0;
        var def = (newDefField.text.length>0)?newDefField.text.valueOf():0;
        var over = (newOverField.text.length>0)?newOverField.text.valueOf():0;

        if(name.length > 0)
            weaponsView.model.append({"name":name,"acc":acc, "atk":(!!atk)?atk:0, "def":(!!def)?def:0, "over":(!!over)?over:0});

    }

}
