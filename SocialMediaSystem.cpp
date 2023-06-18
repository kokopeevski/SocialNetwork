#include "SocialMediaSystem.h"
#include "GlobalConstants.h"
#include "helpers.h"

using namespace DATABASES_FILENAMES;
using namespace LENGTHS;
using namespace COMMANDS;

void SocialMediaSystem::load()
{
	users.load(USER_DBS);
	topics.load(TOPIC_DBS);
	posts.load(POST_DBS);
	comments.load(COMMENT_DBS);
	replies.load(REPLY_DBS);
	reactions.load(REACTION_DBS);
}

void SocialMediaSystem::close()
{
	users.overwrite(USER_DBS);
	topics.overwrite(TOPIC_DBS);
	posts.overwrite(POST_DBS);
	comments.overwrite(COMMENT_DBS);
	replies.overwrite(REPLY_DBS);
	reactions.overwrite(REACTION_DBS);
}

void SocialMediaSystem::registerUser()
{
	User newUser;
	char input[1024];

	print("First names should begin with latin upper letter and have only lower symbols!\n");
	print("Password should have 1 digit, 1 upper and 1 lower letter and at least 6 length!\n\n");

	while (true)
	{
		print("Enter a unique first name: ");
		std::cin.getline(input, MAX_LEN_COMMAND);

		if (users.getByFirstName(input))
		{
			print("This name isn't available. Try again!\n");
		}

		else if (!newUser.setFirstName(input))
		{
			print("Invalid name format, without spaces!\n");
		}
		else
			break;
	}

	while (true)
	{
		print("Enter last name: ");
		std::cin.getline(input, MAX_LEN_COMMAND);

		if (!newUser.setLastName(input))
		{
			print("Invalid last name!\n");
		}
		else
			break;
	}

	while (true)
	{
		print("Enter password: ");
		std::cin.getline(input, MAX_LEN_COMMAND);

		if (!newUser.setPassword(input))
		{
			print("Invalid password format!\n");
		}
		else
			break;
	}

	newUser.setId(users.getUnusedId());
	users.addRecord(newUser);
	print("Success!\n");
}

void SocialMediaSystem::loginUser()
{
	MyString input;
	User* user;

	while (true)
	{
		print("Enter your unique first name: ");

		std::cin >> input;

		user = users.getByFirstName(input);

		if (user == nullptr)
			print("Invalid first name!\n");
		else
			break;
	}

	while (true)
	{
		print("Enter your password: ");

		std::cin >> input;

		if (user->comparePassword(input))
		{
			std::cout << "Welcome back, " << user->getFirstName() << ' '
				<< user->getLastName() << '!' << std::endl << std::endl;
			break;
		}

		print("Invalid password! Try again\n");

	}

	currentUserId = user->getId();

}

void SocialMediaSystem::searchTopics(const MyString& title)
{
	MyVector<Topic> result = topics.searchTopicsByPartOfTitle(title);

	for (size_t i = 0; i < result.getSize(); i++)
	{
		std::cout << "  << " << result[i].getTitle() << " {id:"
			<< result[i].getId() << "}" << std::endl;
	}
}

void SocialMediaSystem::openTopic(const MyString& topicIndetifier)
{
	Topic* currentTopic = nullptr;

	if (isInputValidIndex(topicIndetifier))
	{
		int topicId;
		topicIndetifier >> topicId;

		currentTopic = topics.getById(topicId);
	}
	else
	{
		currentTopic = topics.getByTitle(topicIndetifier);
	}

	if (currentTopic == nullptr)
	{
		print("Invalid topic id or title!\n");
		return;
	}

	handleTopicSession(*currentTopic);
}

void SocialMediaSystem::createTopic()
{
	MyString input;
	Topic topic;

	print("Enter topic title: ");
	std::cin >> input;
	topic.setTitle(input);

	print("Enter topic description: ");
	std::cin >> input;
	topic.setDescription(input);

	topic.setCreaterId(currentUserId);
	topic.setId(topics.getUnusedId());

	topics.addRecord(topic);

	print(MESSAGES::SUCCESS);
}

void SocialMediaSystem::showTopicInfo(const MyString& topicIdentifier)
{
	Topic* currentTopic = nullptr;

	if (isInputValidIndex(topicIdentifier))
	{
		int topicId;
		topicIdentifier >> topicId;

		currentTopic = topics.getById(topicId);
	}
	else
	{
		currentTopic = topics.getByTitle(topicIdentifier);
	}

	if (currentTopic == nullptr)
	{
		print("Invalid topic id or title!\n");
		return;
	}

	const MyString& creater = users.getById(currentTopic->getCreaterId())->getFirstName();
	const MyVector<Post> postsToTopic = posts.getPostsByTopicId(currentTopic->getId());

	std::cout << " >> Title: " << currentTopic->getTitle() << std::endl
		<< " >> Description: " << currentTopic->getDescription() << std::endl
		<< " >> Created by: " << creater << std::endl
		<< " >> Questions: " << postsToTopic.getSize() << std::endl;
}

void SocialMediaSystem::listPostsForTopic(size_t topicId)
{
	MyVector<Post> postsForTopic = posts.getPostsByTopicId(topicId);

	for (size_t i = 0; i < postsForTopic.getSize(); i++)
	{
		std::cout << ">> " << postsForTopic[i].getTitle()
			<< " {id:" << postsForTopic[i].getId() << '}' << std::endl;
	}
}

void SocialMediaSystem::createPost(size_t topicId)
{
	MyString input;
	Post post;

	print("Enter post title: ");
	std::cin >> input;
	post.setTitle(input);

	post.setTopicId(topicId);
	post.setCreaterId(currentUserId);
	post.setId(posts.getUnusedId());

	posts.addRecord(post);
	print(MESSAGES::SUCCESS);
}

void SocialMediaSystem::openPostForTopic(size_t topicId, const MyString& postIndetifier)
{
	Post* currentPost = nullptr;

	if (isInputValidIndex(postIndetifier))
	{
		int postId;
		postIndetifier >> postId;
		currentPost = posts.getById(postId);
	}
	else
	{
		currentPost = posts.getByTitleAndTopicId(postIndetifier, topicId);
	}

	if (currentPost == nullptr)
	{
		print("Invalid post id or title!\n");
		return;
	}

	std::cout << "Post: " << currentPost->getTitle() << std::endl;
	handlePostSession(*currentPost);
}

void SocialMediaSystem::listCommentsForPost(size_t postId)
{
	MyVector<Comment> postsForTopic = comments.getCommentsByPostId(postId);

	for (size_t i = 0; i < postsForTopic.getSize(); i++)
	{
		std::cout << ">> " << postsForTopic[i].getText()
			<< " {id:" << postsForTopic[i].getId() << '}' << std::endl;
	}
}

void SocialMediaSystem::createComment(size_t postId)
{
	MyString input;
	Comment comment;

	print("Enter comment: ");
	std::cin >> input;
	comment.setText(input);

	comment.setPostId(postId);
	comment.setCreaterId(currentUserId);
	comment.setId(comments.getUnusedId());

	users.getById(currentUserId)->addPoints(1);

	comments.addRecord(comment);
	print(MESSAGES::SUCCESS);
}

void SocialMediaSystem::createReply(size_t commentId)
{
	MyString input;
	Reply reply;

	print("Enter reply: ");
	std::cin >> input;
	reply.setText(input);

	reply.setCommentId(commentId);
	reply.setCreaterId(currentUserId);
	reply.setId(topics.getUnusedId());

	replies.addRecord(reply);
	print(MESSAGES::SUCCESS);
}

void SocialMediaSystem::createUpvote(size_t commentId)
{
	Reaction* reaction = reactions.getReactionByUserIdAndCommentId(currentUserId, commentId);

	if (!reaction)
	{
		Reaction newReaction;
		newReaction.setId(reactions.getUnusedId());
		newReaction.setCommentId(commentId);
		newReaction.setCreaterId(currentUserId);
		newReaction.setReactionType(true);
		reactions.addRecord(newReaction);
		print("You've reacted with upvote!\n");
	}
	else
	{
		if (reaction->getIsUpvote())
		{
			reactions.removeReactionById(reaction->getId());
			print("You've removed your upvote!\n");
		}
		else
			print("You've reacted with downvote on this comment!You can't react with upvote!\n");
	}
}

void SocialMediaSystem::createDownvote(size_t commentId)
{
	Reaction* reaction = reactions.getReactionByUserIdAndCommentId(currentUserId, commentId);

	if (!reaction)
	{
		Reaction newReaction;
		newReaction.setId(reactions.getUnusedId());
		newReaction.setCommentId(commentId);
		newReaction.setCreaterId(currentUserId);
		newReaction.setReactionType(false);
		reactions.addRecord(newReaction);
		print("You've reacted with downvote!\n");
	}
	else
	{
		if (!reaction->getIsUpvote())
		{
			reactions.removeReactionById(reaction->getId());
			print("You've removed you downvote!\n");
		}
		else
			print("You've reacted with upvote on this comment!You can't react with downvote!\n");
	}
}

void SocialMediaSystem::showUserInfo()
{
	User* currentUser = users.getById(currentUserId);

	std::cout << currentUser->getFirstName()
		<< " " << currentUser->getLastName()
		<< ", having " << currentUser->getPoints()
		<< " points." << std::endl;
}

void SocialMediaSystem::handleUserSession()
{
	MyString input;

	while (true)
	{
		if (currentUserId == 0)
			return;

		std::cin >> input;
		MyVector<MyString> commandAndValue = splitInputInCommandAndValue(input);
		MyString& command = commandAndValue[0];

		if (commandAndValue.getSize() == 2)
		{
			if (command == SEARCH_TOPIC_BY_TITLE)
			{
				searchTopics(commandAndValue[1]);
			}
			else if (command == OPEN_TOPIC)
			{
				openTopic(commandAndValue[1]);
			}
			else if (command == TOPIC_INFO)
			{
				showTopicInfo(commandAndValue[1]);
			}
			else
			{
				print(MESSAGES::INVALID_COMMAND);
			}
		}
		else if (command == CREATE_TOPIC)
		{
			createTopic();
		}
		else if (command == SHOW_USER_INFO)
		{
			showUserInfo();
		}
		else if (command == LOGOUT || command == EXIT_SYSTEM)
		{
			currentUserId = 0;
			print("You've exited your profile!\n");
			return;
		}
		else
		{
			print(MESSAGES::INVALID_COMMAND);
		}
	}
}

void SocialMediaSystem::handleTopicSession(Topic& currentTopic)
{
	std::cout << "Welcome to \"" << currentTopic.getTitle() << "\"!\n";

	MyString input;
	while (true)
	{
		if (currentUserId == 0)
			return;

		std::cin >> input;
		MyVector<MyString> commandAndValue = splitInputInCommandAndValue(input);
		MyString& command = commandAndValue[0];

		if (command == OPEN_POST)
		{
			if (commandAndValue.getSize() <= 1)
			{
				print(MESSAGES::INVALID_COMMAND);
				continue;
			}
			openPostForTopic(currentTopic.getId(), commandAndValue[1]);
		}
		else if (command == CREATE_POST)
		{
			createPost(currentTopic.getId());
		}
		else if (command == LIST_POSTS)
		{
			listPostsForTopic(currentTopic.getId());
		}
		else if (command == EXIT_SYSTEM)
		{
			currentUserId = 0;
		}
		else if (command == EXIT_TOPIC)
		{
			break;
		}
		else
		{
			print(MESSAGES::INVALID_COMMAND);
		}
	}
}

void SocialMediaSystem::handlePostSession(Post& currentPost)
{
	std::cout << "Welcome to \"" << currentPost.getTitle() << "\"!\n";

	MyString input;
	while (true)
	{
		if (currentUserId == 0)
			return;

		std::cin >> input;

		if (input == CREATE_COMMENT)
		{
			createComment(currentPost.getId());
		}
		else if (input == LIST_COMMENTS)
		{
			listCommentsForPost(currentPost.getId());
		}
		else if (input == EXIT_POST)
		{
			break;
		}
		else if (input == EXIT_SYSTEM)
		{
			currentUserId = 0;
			return;
		}
		else
		{
			MyVector<MyString> commandAndValue = splitInputInCommandAndValue(input);
			MyString& command = commandAndValue[0];
			MyString value = (commandAndValue.getSize() == 2) ? commandAndValue[1] : MyString("empty");

			if (!isInputValidIndex(value))
			{
				print(MESSAGES::INVALID_INDEX);
				continue;
			}

			int commentId;
			value >> commentId;

			Comment* comment = comments.getById(commentId);

			if (comment == nullptr)
			{
				print(MESSAGES::INVALID_INDEX);
				continue;
			}

			if (command == REPLY_BY_ID)
			{
				createReply(commentId);
			}
			else if (command == UPVOTE_BY_ID)
			{
				createUpvote(commentId);
			}
			else if (command == DOWNVOTE_BY_ID)
			{
				createDownvote(commentId);
			}
			else
				print(MESSAGES::INVALID_COMMAND);
		}
	}
}

void SocialMediaSystem::run()
{
	load();
	print("Welcome to The Best Media!\n");
	print("Choose to 'register' or 'login' (Type one of them)!\n");

	while (true)
	{
		MyString input;
		std::cin >> input;

		if (input == REGISTER)
		{
			registerUser();
		}
		else if (input == LOGIN)
		{
			loginUser();
			handleUserSession();
		}
		else if (input == EXIT_SYSTEM)
		{
			print(MESSAGES::EXIT_SYSTEM);
			break;
		}
		else
		{
			print(MESSAGES::INVALID_COMMAND);
		}
	}

	close();
}