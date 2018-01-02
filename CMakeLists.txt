cmake_minimum_required(VERSION 3.8)
project(AP1_ex3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread -Wextra")

set(CORE_FILES
		# utilities
		src/easy_logging/easylogging++.h
		src/game/utilities/GameUtilities.cpp src/game/utilities/GameUtilities.h
        src/display/Display.cpp src/display/Display.h
		# players
		src/game/players/AI.cpp src/game/players/AI.h
		src/game/players/Participant.cpp src/game/players/Participant.h
		src/game/players/Player.cpp src/game/players/Player.h
		# game Logic
		src/game/game_logic/TurnsManager.cpp src/game/game_logic/TurnsManager.h
		src/game/game_logic/MovesEvaluator.cpp src/game/game_logic/MovesEvaluator.h
		# game Flow
        src/game/game_flow/Reversi.cpp src/game/game_flow/Reversi.h
		# board
		src/game/board/Board.cpp src/game/board/Board.h
		src/game/board/Cell.h
		src/game/board/CellIndex.cpp src/game/board/CellIndex.h
        # generator
        src/server/model/reversi_game/generator/ReversiGameGenerator.cpp src/server/model/reversi_game/generator/ReversiGameGenerator.h)

set(SERVER_FILES
        # Server Files
		src/server/server_side/Server.cpp
		src/server/server_side/Server.h
		# Controller
		src/server/controller/Controller.cpp src/server/controller/Controller.h
		src/server/controller/commands/command_list/JoinCommand.cpp
		src/server/view/IClientHandler.h
		src/server/controller/IGameEventHandler.h
        # Commands - inside Controller
        src/server/controller/commands/ICommand.h
        src/server/controller/commands/ServerCommand.h
        src/server/controller/commands/command_list/JoinCommand.h
		src/server/controller/commands/command_list/CloseCommand.cpp src/server/controller/commands/command_list/CloseCommand.h
		src/server/controller/commands/command_list/ListCommand.cpp src/server/controller/commands/command_list/ListCommand.h
		src/server/controller/commands/command_list/PlayCommand.cpp src/server/controller/commands/command_list/PlayCommand.h
		src/server/controller/commands/command_list/StartCommand.cpp src/server/controller/commands/command_list/StartCommand.h
        # Notifier
        src/server/view/IClientNotifier.h)

set(POOL_THREADING
		# tasks
		src/server/thread_pool/tasks/ClientTask.cpp src/server/thread_pool/tasks/ClientTask.h

		# Thread Pool
        src/server/thread_pool/PoolWorkerThread.cpp src/server/thread_pool/PoolWorkerThread.h
        src/server/thread_pool/Task.h
        src/server/thread_pool/Thread.cpp src/server/thread_pool/Thread.h
        src/server/thread_pool/ThreadPool.cpp src/server/thread_pool/ThreadPool.h
        src/server/thread_pool/WorkQueue.cpp src/server/thread_pool/WorkQueue.h)

set(SHARED_DATA_FILES
		src/shared_data/Notification.cpp src/shared_data/Notification.h
		src/shared_data/utility/StringSerializing.cpp src/shared_data/utility/StringSerializing.h
		src/shared_data/Message.cpp src/shared_data/Message.h
		src/shared_data/CommandResult.cpp src/shared_data/CommandResult.h
		src/shared_data/MoveUpdate.cpp src/shared_data/MoveUpdate.h)

set(CLIENT_FILES
		# ServerClient
        src/server/IClient.h
		src/server/view/ServerClient.cpp src/server/view/ServerClient.h
		# ServerClient Handling
		src/server/view/ClientHandler.cpp src/server/view/ClientHandler.h)

set(MODEL_FILES
        # IModel
        src/server/model/IModel.h
        # Model
        src/server/model/Model.cpp src/server/model/Model.h
        # Requests
        src/server/model/requests/IRequest.h
        src/server/model/requests/JoinRequesst.cpp src/server/model/requests/JoinRequest.h
        src/server/model/requests/StartRequest.cpp src/server/model/requests/StartRequest.h
        src/server/model/requests/CloseRequest.cpp src/server/model/requests/CloseRequest.h
        src/server/model/requests/PlayRequest.cpp src/server/model/requests/PlayRequest.h
        src/server/model/game_manager/IGameManager.h
        src/server/model/game_manager/IGameContainer.h
        src/server/model/reversi_game/generator/IGameGenerator.h
        src/server/model/game_manager/GameManager.cpp src/server/model/game_manager/GameManager.h
        src/server/model/game_manager/ListGameContainer.cpp src/server/model/game_manager/ListGameContainer.h
        src/server/model/reversi_game_manager/IReversiGameManager.h
        src/server/model/reversi_game_manager/ReversiGameManager.cpp src/server/model/reversi_game_manager/ReversiGameManager.h
        src/server/model/reversi_game/ReversiGameEvent.h src/server/model/reversi_game/ReversiGameEvent.cpp
        src/server/model/reversi_game/ReversiGame.cpp src/server/model/reversi_game/ReversiGame.h
        src/server/model/reversi_game/ReversiGamePlayer.cpp src/server/model/reversi_game/ReversiGamePlayer.h)

set(ONLINE_PLAYING_FILES
		${SERVER_FILES}
        ${MODEL_FILES}
		${MESSAGE_FILES}
		${SHARED_DATA_FILES}
		${CLIENT_FILES}
        ${POOL_THREADING})

set(SOURCE_FILES ${CORE_FILES} ${ONLINE_PLAYING_FILES} src/client/Client.cpp src/client/Client.h)

# Adding Executables
add_executable(run_server src/main/server_main.cpp ${SERVER_FILES} ${SOURCE_FILES})
add_executable(run_client src/main/client_main.cpp ${SERVER_FILES} ${SOURCE_FILES})
