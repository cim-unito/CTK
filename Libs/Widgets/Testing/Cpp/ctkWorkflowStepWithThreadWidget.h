/*
 * DceWorkflowStep.h
 *
 *  Created on: 2011.10.04.
 *      Author: espakm
 */

#ifndef __ctkWorkflowStepWithThreadWidget_h
#define __ctkWorkflowStepWithThreadWidget_h

#include <ctkWorkflowWidgetStep.h>
#include <ctkWorkflowTransitions.h>

#include "ctkWorkflowStepThread.h"

#include <QThread>
#include <QString>
#include <QDebug>

class ctkWorkflowStepWithThreadWidget : public ctkWorkflowWidgetStep
{
  Q_OBJECT

public:

  explicit ctkWorkflowStepWithThreadWidget(QWidget* newParent = 0);
  explicit ctkWorkflowStepWithThreadWidget(const QString& newId, QWidget* newParent = 0);
  virtual ~ctkWorkflowStepWithThreadWidget();

protected:
  virtual void onEntry(const ctkWorkflowStep* comingFrom, const ctkWorkflowInterstepTransition::InterstepTransitionType transitionType);
  virtual void onExit(const ctkWorkflowStep* goingTo, const ctkWorkflowInterstepTransition::InterstepTransitionType transitionType);

  void executeAsynchron();

  virtual void execute();

//  void observeProcess(itk::ProcessObject* process, QString statusMessage);

protected slots:
  /// Notified when the workflow step started being executed
  virtual void onExecutionStarted();
  /// Notified when the execution of the workflow step has finished
  virtual void onExecutionFinished();
  /// Notified when the execution of the workflow step has terminated
  virtual void onExecutionTerminated();

  /// Notified when an internal process has been started during the execution
  virtual void onProcessStarted(QString message) {
  }
  /// Notified of the progress of an internal process
  virtual void onProcessProgress(double progress) {
  }
//  virtual void onProcessTerminated() {}
  /// Notified when an internal process has finished
  virtual void onProcessFinished() {
  }

private:
  ctkWorkflowStepThread* thread;

  friend class ctkWorkflowStepThread;

};

#endif /* __ctkWorkflowStepWithThreadWidget_h */
