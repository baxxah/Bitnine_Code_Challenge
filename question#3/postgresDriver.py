from flask import Flask, jsonify 
from flask_sqlalchemy import SQLAlchemy
import config

app = Flask(__name__)

db_uri = f"postgresql://{config.DB_USER}:{config.DB_PASSWORD}@{config.DB_HOST}:{config.DB_PORT}/{config.DB_NAME}"
app.config["SQLALCHEMY_DATABASE_URI"] = db_uri

db = SQLAlchemy(app)

class User(db.Model):
  __tablename__ = "user_table"
  user_id = db.Column(db.Integer, primary_key=True)
  name = db.Column(db.String(50), nullable=False)
  age = db.Column(db.Integer, nullable=False)
  phone = db.Column(db.String(20))

  def __init__(self, user_id, name, age, phone):
    self.user_id = user_id
    self.name = name
    self.age = age
    self.phone = phone

  def to_dict(self):
    return {
        "user_id": str(self.user_id),
        "name": self.name,
        "age": str(self.age),
        "phone": self.phone,
    }
with app.app_context():
    db.drop_all()
    db.create_all()
    db.session.commit() 

with app.app_context():
  user1 = User(3, 'Jenny', 34, None)
  user2 = User(2, 'Tom', 29, '1-800-123-1234')
  user3 = User(1, 'John', 28, None)

  db.session.add_all([user1, user2, user3])
  db.session.commit()

@app.route("/")
def get_users():
  try: 
    users =User.query.all()
    user_dicts = [user.to_dict() for user in users]
    json_data = jsonify({"status_code": 200, "data": user_dicts})
    return json_data
  except Exception as e:
    return jsonify({"error":  str(e)}), 500
    
if __name__ == "__main__":
  app.run(port=3000)