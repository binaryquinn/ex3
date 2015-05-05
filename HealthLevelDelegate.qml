import QtQuick 2.4

HealthLevelDelegateForm
{
    hlColumn.onUp:
    {
        if(hlRepeater.model< 15)
        {
            if(hlRepeater.model>0 &&hlRepeater.model%5 == 0) height+=21
            hlRepeater.model++
        }

    }

    hlColumn.onDown:
    {
        if(hlRepeater.model > 0)
        {
            hlRepeater.model--
            if(hlRepeater.model%5 == 0 && hlRepeater.model > 0) height -= 21
        }
    }
}

