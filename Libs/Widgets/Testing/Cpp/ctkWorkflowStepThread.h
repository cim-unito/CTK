/*
 * ctkWorkflowStepThread.h
 *
 *  Created on: 2011.10.24.
 *      Author: espakm
 */

#ifndef ctkWorkflowStepThread_H_
#define ctkWorkflowStepThread_H_

#include <QThread>

class ctkWorkflowStepWithThreadWidget;

//namespace itk
//{
//class ProcessObject;
//}

class ctkWorkflowStepThread : public QThread
{
  Q_OBJECT

public:
  ctkWorkflowStepThread(ctkWorkflowStepWithThreadWidget* workflowStep);

  virtual ~ctkWorkflowStepThread();

signals:
  void processStarted(QString message);
  void processProgress(double);
  void processFinished();

protected:
  virtual void run();

public:
//  void observeProcess(itk::ProcessObject* process, QString statusMessage);

private:
  void onStartEvent();

  void onEndEvent();

  void onProgressEvent();

private:
  ctkWorkflowStepWithThreadWidget* workflowStep;

//  itk::ProcessObject* process;
  QString statusMessage;

public:
  QString errorMessage;
  QString detailedMessage;
};

#endif /* ctkWorkflowStepThread_H_ */
