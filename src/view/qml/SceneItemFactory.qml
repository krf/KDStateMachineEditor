/*
  SceneItemFactory.qml

  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
  All rights reserved.
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB State Machine Editor Library
  licenses may use this file in accordance with the KDAB State Machine Editor
  Library License Agreement provided with the Software.

  This file may be distributed and/or modified under the terms of the
  GNU Lesser General Public License version 2.1 as published by the
  Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.

  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Contact info@kdab.com if any conditions of this licensing are not
  clear to you.
*/

import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

import com.kdab.kdsme 1.0

import "uml/"

Loader {
    id: root

    property var configurationController
    property var view

    x: object.pos.x
    y: object.pos.y

    asynchronous: true

    sourceComponent: {
        if (object.type === Element.StateMachineType) {
            return umlStateMachine;
        } else if (object.type === Element.FinalStateType) {
            return umlFinalState;
        } else if (object.type === Element.HistoryStateType) {
            return umlHistoryState;
        } else if (object.type === Element.PseudoStateType) {
            return umlPseudoState;
        } else if (object.type === Element.StateType) {
            return umlState;
        } else if (object.type === Element.TransitionType) {
            return umlTransition;
        } else if (object.type === Element.SignalTransitionType) {
            return umlTransition; // no special representation for now
        } else if (object.type === Element.TimeoutTransitionType) {
            return umlTransition; // no special representation for now
        } else {
            console.log("Unknown Element type: " + object.type);
            return null;
        }
    }

    function activenessForState(state) {
        configurationController.activeConfiguration; // bind to active configuration
        return configurationController.activenessForState(state);
    }

    function activenessForTransition(transition) {
        configurationController.activeConfiguration; // bind to active configuration
        return configurationController.activenessForTransition(transition)
    }



    Component {
        id: umlState
        UmlState {
            element: object
            activeness: activenessForState(object)
        }
    }

    Component {
        id: umlStateMachine
        UmlStateMachine {
            element: object
        }
    }

    Component {
        id: umlFinalState
        UmlFinalState {
            element: object
            activeness: activenessForState(object)
        }
    }

    Component {
        id: umlHistoryState
        UmlHistoryState {
            element: object
            activeness: activenessForState(object)
        }
    }

    Component {
        id: umlPseudoState
        UmlPseudoState {
            element: object
            activeness: activenessForState(object)
        }
    }

    Component {
        id: umlTransition
        UmlTransition {
            element: object
            activeness: activenessForTransition(object)
        }
    }
}