import QtQuick 2.4

HealthLevelDelegateForm
{
    property var parentModel;
    hlColumn.onUp:
    {
        if(hlRepeater.model< 15)
        {
            if(hlRepeater.model>0 &&hlRepeater.model%5 == 0) height+=21
            parentModel.set(delegateIndex, {"hlCount":hlRepeater.model+1});
        }

    }

    hlColumn.onDown:
    {
        if(hlRepeater.model > 0)
        {
            parentModel.set(delegateIndex, {"hlCount":hlRepeater.model-1});
            if(hlRepeater.model%5 == 0 && hlRepeater.model > 0) height -= 21
        }
    }
}

