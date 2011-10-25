/*
 * ctkWorkflowStepThread.cpp
 *
 *  Created on: 2011.10.24.
 *      Author: espakm
 */

#include "ctkWorkflowStepThread.h"
#include "ctkWorkflowStepWithThreadWidget.h"

//#include <itkCommand.h>
//#include <itkProcessObject.h>

ctkWorkflowStepThread::ctkWorkflowStepThread(ctkWorkflowStepWithThreadWidget* workflowStep)
: workflowStep(workflowStep)
{
//  process = 0;
  connect(this, SIGNAL(started()), workflowStep, SLOT(onExecutionStarted()));
  connect(this, SIGNAL(terminated()), workflowStep, SLOT(onExecutionTerminated()));
  connect(this, SIGNAL(finished()), workflowStep, SLOT(onExecutionFinished()));
  connect(this, SIGNAL(processStarted(QString)), workflowStep, SLOT(onProcessStarted(QString)));
  connect(this, SIGNAL(processProgress(double)), workflowStep, SLOT(onProcessProgress(double)));
  connect(this, SIGNAL(processFinished()), workflowStep, SLOT(onProcessFinished()));
}

ctkWorkflowStepThread::~ctkWorkflowStepThread()
{
}

void
ctkWorkflowStepThread::run()
{
  try {
    workflowStep->execute();
    workflowStep->onExitComplete();
  }
  catch (std::exception& exception) {
    errorMessage = tr("Error occurred during the calculation.\n");
    detailedMessage = tr(exception.what());
    throw;
  }
}

//void
//ctkWorkflowStepThread::observeProcess(itk::ProcessObject* process, QString statusMessage) {
//  this->process = process;
//  this->statusMessage = statusMessage;
//
//  typedef itk::SimpleMemberCommand<ctkWorkflowStepThread> MemberCommand;
//
//  MemberCommand::Pointer startCommand = MemberCommand::New();
//  startCommand->SetCallbackFunction(this, &ctkWorkflowStepThread::onStartEvent);
//  process->AddObserver(itk::StartEvent(), startCommand);
//
//  MemberCommand::Pointer endCommand = MemberCommand::New();
//  endCommand->SetCallbackFunction(this, &ctkWorkflowStepThread::onEndEvent);
//  process->AddObserver(itk::EndEvent(), endCommand);
//
//  MemberCommand::Pointer progressCommand = MemberCommand::New();
//  progressCommand->SetCallbackFunction(this, &ctkWorkflowStepThread::onProgressEvent);
//  process->AddObserver(itk::ProgressEvent(), progressCommand);
//}

void
ctkWorkflowStepThread::onStartEvent() {
  emit processStarted(statusMessage);
}

void
ctkWorkflowStepThread::onEndEvent() {
  emit processFinished();
}

void
ctkWorkflowStepThread::onProgressEvent() {
//  emit processProgress(process->GetProgress());
}
