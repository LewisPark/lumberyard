/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

// include the required headers
#include "NodeSelectionWindow.h"
#include "EMStudioManager.h"
#include <MCore/Source/LogManager.h>
#include <EMotionFX/Source/Mesh.h>
#include <QLabel>
#include <QSizePolicy>
#include <QTreeWidget>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>


namespace EMStudio
{
    // constructor
    NodeSelectionWindow::NodeSelectionWindow(QWidget* parent, bool useSingleSelection)
        : QDialog(parent)
    {
        mAccepted = false;
        setWindowTitle("Node Selection Window");

        QVBoxLayout* layout = new QVBoxLayout();

        mHierarchyWidget = new NodeHierarchyWidget(this, useSingleSelection);

        // create the ok and cancel buttons
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        mOKButton       = new QPushButton("OK");
        mCancelButton   = new QPushButton("Cancel");
        buttonLayout->addWidget(mOKButton);
        buttonLayout->addWidget(mCancelButton);

        layout->addWidget(mHierarchyWidget);
        layout->addLayout(buttonLayout);
        setLayout(layout);

        connect(mOKButton, SIGNAL(clicked()), this, SLOT(accept()));
        connect(mCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
        connect(this, SIGNAL(accepted()), this, SLOT(OnAccept()));
        connect(mHierarchyWidget, SIGNAL(OnDoubleClicked(MCore::Array<SelectionItem>)), this, SLOT(OnDoubleClicked(MCore::Array<SelectionItem>)));

        // connect the window activation signal to refresh if reactivated
        //connect( this, SIGNAL(visibilityChanged(bool)), this, SLOT(OnVisibilityChanged(bool)) );

        // set the selection mode
        mHierarchyWidget->SetSelectionMode(useSingleSelection);
        mUseSingleSelection = useSingleSelection;
    }


    // destructor
    NodeSelectionWindow::~NodeSelectionWindow()
    {
    }


    void NodeSelectionWindow::OnDoubleClicked(MCore::Array<SelectionItem> selection)
    {
        MCORE_UNUSED(selection);
        accept();
    }


    void NodeSelectionWindow::OnAccept()
    {
        mHierarchyWidget->FireSelectionDoneSignal();
    }
} // namespace EMStudio

#include <EMotionFX/Tools/EMotionStudio/EMStudioSDK/Source/NodeSelectionWindow.moc>