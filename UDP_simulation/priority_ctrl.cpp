#include "priority_ctrl.h"
#include "priority.h"


priority_ctrl::priority_ctrl(int id) :
  currentState(state_idle),
  myPriority(id){
    connect(&user_list_timer, SIGNAL(timeout()), this, SLOT(timeout_send_name()));
    user_list_timer.start(user_update_timeout);
}

void priority_ctrl::process(Event e, QString data)
{

    //this event do not depend of the the current state
    if( e == Event::e_update_name){
        //received an id to update the user list
        myPriority.updateName(data);
        return;
    }

    switch (currentState)
    {
        case state_idle:
            qDebug() << "State: state_idle";

            if( e == Event::e_send){
                //PTT button pressed
                currentState = State::state_rts;
                myPriority.sendRequestToSend(data);
                //state_rts entry Point
                rts_timer.setSingleShot(true);
                connect(&rts_timer, SIGNAL(timeout()), this, SLOT(rts_timeout()));
                rts_timer.start(t_timeout);

                break;
            }

            if(e == Event::e_recv_audio_data){
                //Audio data packet received
                myPriority.reproduceAudio(data);
                break;
            }

            if(e == Event::e_request_received){
                //Received a request to send from another user
                currentState = State::state_cts;

                // state_cts entry Point
                cts_timer.setSingleShot(true);
                connect(&rts_timer, SIGNAL(timeout()), this, SLOT(rts_timeout()));
                cts_timer.start(t_timeout);

                myPriority.answerRequestToSend(data,true);

                break;
            }


        break;

        case state_cts:
            qDebug() << "State: state_cts";

            if(e == Event::e_request_received){
                //Received a request of sending from another user
                myPriority.answerRequestToSend(data,false);
                break;
            }

            if(e == Event::e_recv_audio_data){
                //Audio data packet received
                myPriority.reproduceAudio(data);
                break;
            }

        break;

        case state_rts:
            qDebug() << "State: state_rts";

            if(e == Event::e_request_received){
                //Received a request to send from another user
                myPriority.answerRequestToSend(data,false);
                myPriority.addRequestToList(data);
                break;
            }

            if(e == Event::e_answer_to_rts){
                //received an answer to a request to send
                myPriority.addAnswerToList(data);
                break;
            }

            if(e == Event::e_recv_audio_data){
                //Audio data packet received
                myPriority.reproduceAudio(data);

                //someone is already transmitting
                currentState = State::state_idle;
                rts_timer.stop();
                break;
            }
        break;

        case state_sending:
            qDebug() << "State: state_sending";

            if(e == Event::e_stop_send){
                //PTT button released
                currentState = State::state_idle;
                break;
            }

            if(e == Event::e_send_audio_data){
                //audio data available to be sent
                myPriority.sendAudio(data);
                break;
            }

        break;

        default:
        break;
    }
}

void priority_ctrl::rts_timeout(){
    qDebug() << "rts_timeout";
    bool answer = myPriority.evaluateList();
    if(answer){
        qDebug() << "permission_confirmed";
        currentState = State::state_sending;
    }else{
        qDebug() << "permission_denied";
        currentState = State::state_idle;
    }
    myPriority.clear_request_list();
    myPriority.clear_answer_list();
}

void priority_ctrl::cts_timeout(){
    qDebug() << "cts_timeout";
    currentState = State::state_idle;
    myPriority.clear_request_list();
}

priority_ctrl::~priority_ctrl(){
    qDebug() << "FSM deleted";
}

void priority_ctrl::timeout_send_name(){
    myPriority.send_name();
}

