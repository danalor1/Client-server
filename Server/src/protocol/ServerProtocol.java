package protocol;

import java.util.HashMap;

/**
 * A protocol that describes the behavior of the server.
 */
public interface ServerProtocol<T> {

	/**
     * processes a message
     * @param msg the message to process
     * @return the reply that should be sent to the client, or null if no reply needed
     */
	T processMessage(T msg);

	T processMessage(T msg,HashMap<String,String> historyMessage,HashMap<String,String> users,
			HashMap<String,String> userAuth,HashMap<String,HashMap<String,String>> groups);
	/**
     * Determine whether the given message is the termination message
     * @param msg the message to examine
     * @return true if the message is the termination message, false otherwise
     */
	boolean isEnd(T msg);

}
