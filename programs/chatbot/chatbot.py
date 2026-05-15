from flask import Flask, request, jsonify
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

def get_bot_response(user_text):
    user_text = user_text.lower()
    
    if "price" in user_text or "cost" in user_text:
        return "Our premium watches start from ₹24,999. The Luxury Classic is currently ₹29,999."
    
    if "model" in user_text or "collection" in user_text:
        return "We feature the 'Classic' and 'Sport' models. Both are water-resistant and durable."
    
    if "shipping" in user_text or "delivery" in user_text:
        return "We offer free worldwide shipping! Delivery usually takes 3-5 business days."
    
    if "process" in user_text or "order" in user_text:
        return "You can place order from our website."
    
    if "hi" in user_text or "hello" in user_text:
        return "Hello! Welcome to Luxury Watch. How can I assist you today?"
        
    return "I'm not sure about this. Could you try asking about prices, models, or shipping?"

@app.route('/chat', methods=['POST'])
def chat():
    data = request.json
    user_message = data.get("message", "")
    response = get_bot_response(user_message)
    return jsonify({"response": response})

if __name__ == '__main__':
    app.run(port=5000)