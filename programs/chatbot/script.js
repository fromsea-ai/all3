function toggleChat() {
    const chat = document.getElementById('chat-container');
    const displayStatus = chat.style.display;
    
    if (displayStatus === 'none' || displayStatus === '') {
        chat.style.display = 'flex';
    } else {
        chat.style.display = 'none';
    }
}

async function sendMessage() {
    const inputField = document.getElementById('user-input');
    const chatBox = document.getElementById('chat-box');
    const userText = inputField.value.trim();

    if (userText === "") return;

    chatBox.innerHTML += `<div style="margin-bottom: 8px;"><strong>You:</strong> ${userText}</div>`;
    inputField.value = "";
    chatBox.scrollTop = chatBox.scrollHeight;

    try {
        const response = await fetch('http://127.0.0.1:5000/chat', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ message: userText })
        });

        if (!response.ok) throw new Error("Server not responding");

        const data = await response.json();

        setTimeout(() => {
            chatBox.innerHTML += `<div style="margin-top:5px; color: darkred; margin-bottom: 8px;"><strong>Bot:</strong> ${data.response}</div>`;
            chatBox.scrollTop = chatBox.scrollHeight;
        }, 400);

    } catch (error) {
        chatBox.innerHTML += `<div style="color: grey; font-size: 12px; margin-top: 5px;"><em>Error: Python server is not running.</em></div>`;
        chatBox.scrollTop = chatBox.scrollHeight;
    }
}

document.getElementById("user-input").addEventListener("keypress", function(event) {
    if (event.key === "Enter") {
        sendMessage();
    }
});