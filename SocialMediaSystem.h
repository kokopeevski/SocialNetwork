#pragma once
#include "DataTable.hpp"
#include "User.h"
#include "Topic.h"
#include "Post.h"
#include "Comment.h"
#include "Reply.h"
#include "Reaction.h"

class SocialMediaSystem
{
	DataTable<User> users;
	DataTable<Post> posts;
	DataTable<Topic> topics;
	DataTable<Comment> comments;
	DataTable<Reply> replies;
	DataTable<Reaction> reactions;

	size_t currentUserId = 0;

	void load(); // ready
	void close(); // ready
	void registerUser(); // ready
	void loginUser(); // ready

	void searchTopics(const MyString& title); // ready

	void openTopic(const MyString& topicIndetifier); // ready
	void createTopic(); // ready
	void showTopicInfo(const MyString& topicIdentifier);

	void listPostsForTopic(size_t topicId); // ready
	void createPost(size_t topicId); // ready
	void openPostForTopic(size_t topicId, const MyString& postIndetifier); // ready

	void listCommentsForPost(size_t postId); // halfready
	void createComment(size_t postId); // ready
	void createReply(size_t commentId); // ready
	void createUpvote(size_t commentId); // ready
	void createDownvote(size_t commentId); // ready

	void showUserInfo(); // ready

	void handleUserSession(); // ready
	void handleTopicSession(Topic& currentTopic); // ready
	void handlePostSession(Post& currentPost); // ready

public:
	void run();
	SocialMediaSystem() = default;
	~SocialMediaSystem() = default;
};
