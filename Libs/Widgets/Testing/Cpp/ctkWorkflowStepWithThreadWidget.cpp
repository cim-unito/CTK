/*
 * DceWorkflowStep.cpp
 *
 *  Created on: 2011.10.04.
 *      Author: espakm
 */

#include "ctkWorkflowStepWithThreadWidget.h"

#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QTest>
#include <QtCore>

ctkWorkflowStepWithThreadWidget::ctkWorkflowStepWithThreadWidget(QWidget* newParent)
: ctkWorkflowWidgetStep(newParent)
{
  thread = 0;
}

ctkWorkflowStepWithThreadWidget::ctkWorkflowStepWithThreadWidget(const QString& newId, QWidget* newParent)
: ctkWorkflowWidgetStep(newId, newParent)
{
  thread = 0;
}

ctkWorkflowStepWithThreadWidget::~ctkWorkflowStepWithThreadWidget()
{
  if (thread) {
    thread->wait();
    delete thread;
  }
}

//-----------------------------------------------------------------------------
void ctkWorkflowStepWithThreadWidget::onEntry(const ctkWorkflowStep* comingFrom, const ctkWorkflowInterstepTransition::InterstepTransitionType transitionType)
{
  ctkWorkflowWidgetStep::onEntry(comingFrom, transitionType);
  qDebug() << name() << "onEntry";
//  qDebug() << "comingFrom:" << comingFrom->name();
}

void ctkWorkflowStepWithThreadWidget::onExit(const ctkWorkflowStep* goingTo, const ctkWorkflowInterstepTransition::InterstepTransitionType transitionType)
{
  Q_UNUSED(goingTo);

  qDebug() << name() << "onExit";
  if (transitionType != ctkWorkflowInterstepTransition::TransitionToNextStep)
  {
//    qDebug() << "goingTo:" << goingTo->name();
    // signals that we are finished
    this->onExitComplete();
    return;
  }

  executeAsynchron();
}

//-----------------------------------------------------------------------------
void ctkWorkflowStepWithThreadWidget::executeAsynchron()
{
  if (thread) {
    thread->wait();
    delete thread;
  }
  thread = new ctkWorkflowStepThread(this);
  thread->start();
//  execute();
//  this->onExitComplete();
}

void
ctkWorkflowStepWithThreadWidget::execute()
{
  qDebug() << this->name() << "execution started";
  QTest::qSleep(5000);
  qDebug() << this->name() << "execution finished";
}

//void
//ctkWorkflowStepWithThreadWidget::observeProcess(itk::ProcessObject* process, QString statusMessage)
//{
//  if (thread)
//  {
//    thread->observeProcess(process, statusMessage);
//  }
//}

void
ctkWorkflowStepWithThreadWidget::onExecutionStarted()
{
}

void
ctkWorkflowStepWithThreadWidget::onExecutionFinished()
{
}

void
ctkWorkflowStepWithThreadWidget::onExecutionTerminated()
{
  qDebug() << "on_ExecutionTerminated";
  if (!thread->errorMessage.isNull())
  {
//    showError(thread->errorMessage, thread->detailedMessage);
  }
  delete thread;
  thread = 0;
}
