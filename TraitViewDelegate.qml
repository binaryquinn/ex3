import QtQuick 2.4


TraitViewDelegateForm
{
    property var parentModel;
    traitRatingBox.onActivated:
    {
        parentModel.set(delegateIndex,{"stat": parseInt(traitRatingBox.textAt(index))});
    }
}

