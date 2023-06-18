#pragma once

namespace LENGTHS {
	const size_t MIN_LEN_PASS = 6;
	const size_t MAX_LEN_PASS = 30;
	const size_t MAX_LEN_COMMAND = 1024;
}

namespace DATABASES_FILENAMES {
	const char USER_DBS[] = "users.txt";
	const char TOPIC_DBS[] = "topics.txt";
	const char POST_DBS[] = "posts.txt";
	const char COMMENT_DBS[] = "comments.txt";
	const char REPLY_DBS[] = "replies.txt";
	const char REACTION_DBS[] = "reactions.txt";
}

namespace COMMANDS {
	const char REGISTER[] = "register";
	const char LOGIN[] = "login";
	const char LOGOUT[] = "logout";
	const char SEARCH_TOPIC_BY_TITLE[] = "search";
	const char OPEN_TOPIC[] = "open";
	const char CREATE_TOPIC[] = "topic";
	const char TOPIC_INFO[] = "about";
	const char LIST_POSTS[] = "list";
	const char CREATE_POST[] = "post";
	const char OPEN_POST[] = "p_open";
	const char CREATE_COMMENT[] = "comment";
	const char LIST_COMMENTS[] = "comments";
	const char REPLY_BY_ID[] = "reply";
	const char UPVOTE_BY_ID[] = "upvote";
	const char DOWNVOTE_BY_ID[] = "downvote";
	const char EXIT_POST[] = "p_close";
	const char EXIT_TOPIC[] = "quit";
	const char EXIT_SYSTEM[] = "exit";
	const char SHOW_USER_INFO[] = "whoami";
	const char SHOW_TOPIC_INFO_BY_ID[] = "about";
}

namespace MESSAGES
{
	const char SUCCESS[] = "Success!\n\n";
	const char INVALID_COMMAND[] = "Invalid command!\n\n";
	const char EXIT_SYSTEM[] = "You've exited the system!\n";
	const char INVALID_INDEX[] = "Invalid index\n";
}