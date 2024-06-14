from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/sensor', methods=['POST'])
def sensor_data():
    data = request.get_json()
    if 'temperature' in data:
        temperature = data['temperature']
        print(f"Received temperature: {temperature}")
        return jsonify({"status": "success", "temperature": temperature}), 200
    else:
        return jsonify({"status": "fail", "message": "No temperature data"}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
