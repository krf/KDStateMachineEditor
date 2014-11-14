/*
  LayoutItemLoader.qml

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

Item {
    id: root

    //x: object.pos.x
    //y: object.y
    width: loader.width
    height: loader.height

    property var view
    property var configurationController

    function activenessForState(state) {
        configurationController.activeConfiguration; // bind to active configuration
        return configurationController.activenessForState(state);
    }

    function activenessForTransition(transition) {
        configurationController.activeConfiguration; // bind to active configuration
        return configurationController.activenessForTransition(transition)
    }

    Loader {
        id: loader

        anchors {
            left: parent.left
            top: parent.top
        }

        asynchronous: true

        sourceComponent: {
            //return umlFinalState;
            console.log(object)
            if (object.type === Element.StateMachineType) {
                    return umlStateMachine;
            } else if (object.type === Element.FinalStateType) {
                return umlFinalState;
            } else {
                return null;
            }

            // TODO: Can we make all this more declarative?
            if (object.type === LayoutItem.StateType) {
                if (object.type === Element.StateMachineType) {
                    return umlStateMachine;
                } else if (object.type === Element.FinalStateType) {
                    return umlFinalState;
                } else if (object.type === Element.HistoryStateType) {
                    return umlHistoryState;
                } else if (object.type === Element.PseudoStateType) {
                    return umlPseudoState;
                } else {
                    return umlState;
                }
            } else if (object.type === Element.TransitionType) {
                return umlTransition;
            } else {
                console.log("Unknown LayoutItem type: " + object.type);
                return null;
            }
        }
    }

    Component {
        id: umlState
        UmlState {
            item: object
            activeness: activenessForState(object.element)
        }
    }

    Component {
        id: umlStateMachine
        UmlStateMachine {
            item: object
        }
    }

    Component {
        id: umlFinalState
        UmlFinalState {
            //item: object
            //activeness: activenessForState(object.element)
        }
    }

    Component {
        id: umlHistoryState
        UmlHistoryState {
            item: object
            activeness: activenessForState(object.element)
        }
    }

    Component {
        id: umlPseudoState
        UmlPseudoState {
            item: object
            activeness: activenessForState(object.element)
        }
    }

    Component {
        id: umlTransition
        UmlTransition {
            item: object
            activeness: activenessForTransition(object.element)
        }
    }
}
