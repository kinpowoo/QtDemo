.import QtQuick.LocalStorage 2.0 as Sqlite


function writeObj(obj){
    var description = "";
    for(var i in obj){
        var property=obj[i];
        description+=i+" = "+property+"\n";
    }
    return description
}


function getDb(){
    return Sqlite.LocalStorage.openDatabaseSync("Person_DB","1.0","Person records",1000000)
}


/**
  * 初始化 db
  */
function dbInit(){
    var db = getDb()
    try{
        db.transaction(function(tx){
            tx.executeSql("CREATE TABLE IF NOT EXISTS names(id INTEGER,firstname TEXT,lastname TEXT,age INTEGER)")
        })
    }catch(err){
            console.log("Error creating table in database: "+err)
    }
}


/**
  * 插入一条记录
  */
function insert(param){
    var rowid = 0
    var db = getDb()
    db.transaction(function(tx){
        var res = tx.executeSql("SELECT COUNT(*) FROM names WHERE firstname=? AND lastname=? AND age=?",
                                [param.firstName,param.lastName,param.age])
        var count;
        for(var i in res.rows[0]){
            count = res.rows[0][i];
        }
        if(res.rows.length === 1 && count >=1) {
            console.log("条目已存在,count:"+count)
            rowid = -1
        }else{
            var result = tx.executeSql("SELECT MAX(id) FROM names")
            var maxId;
            for(var j in result.rows[0]){
                maxId = result.rows[0][j];
            }
            console.log("res 结构:"+writeObj(result.rows[0]))
            tx.executeSql("INSERT INTO names VALUES(?,?,?,?)",
                          [maxId+1,param.firstName,param.lastName,param.age])
            var result2 = tx.executeSql("SELECT last_insert_rowid()")
            rowid = result2.insertId
        }
    })
    return rowid
}


/**
  * 删除指定id的记录
  */
function delById(id){
    var isSuccess = false
    var db = getDb()
    db.transaction(function(tx){
        var res = tx.executeSql("DELETE FROM names WHERE id=?",[id])
        if(res.rowsAffected > 0){
            isSuccess = true
        }
    })
    return isSuccess
}


/**
  * 删除所有记录
  */
function delAll(){
    var isSuccess = false
    var db = getDb()
    db.transaction(function(tx){
        var res = tx.executeSql("DELETE FROM names WHERE 1=1")
        if(res.rowsAffected > 0){
            isSuccess = true
        }
    })
    return isSuccess
}


/**
  * 更新指定id的记录
  */
function update(id,param){
    var isSuccess = false
    var db = getDb()
    db.transaction(function(tx){
        var res = tx.executeSql("UPDATE names SET firstname=?,lastname=?,age=? WHERE id=?",
                                [param.firstName,param.lastName,param.age,id])
        if(res.rowsAffected > 0){
            isSuccess = true
        }
    })
    return isSuccess
}

/**
  * 查询指定条件的所有记录
  */
function queryByCond(firstname,lastname){
    var list = [];
    var db = getDb()
    var res
    db.transaction(function(tx){
        res = tx.executeSql("SELECT * FROM names WHERE firstname=? AND lastname=?",[firstname,lastname])
    })
    for(var i=0; i<res.rows.length ;i++){
        var row = res.rows.item(i)
        list.push({
            id:row.id,
            firstName:row.firstname,
            lastName:row.lastname,
            age:row.age
        })
    }
    return list
}

/**
  * 查询最近插入的一条记录
  */
function queryLatestOne(){
    var list = []
    var db = getDb()
    var res
    db.transaction(function(tx){
        var result = tx.executeSql("SELECT last_insert_rowid()")
        console.log("最新的id:"+result.insertId)
        res = tx.executeSql("SELECT * FROM names WHERE id=?",[parseInt(result.insertId)])
    })
    for(var i=0; i<res.rows.length ;i++){
        var row = res.rows.item(i)
        list.push({
            id:row.id,
            firstName:row.firstname,
            lastName:row.lastname,
            age:row.age
        })
    }
    return list
}

/**
  * 查询所有记录
  */
function queryAll(){
    var list = []
    var db = getDb()
    var res
    db.transaction(function(tx){
        res = tx.executeSql("SELECT * FROM names")
    })
    for(var i=0; i<res.rows.length ;i++){
        var row = res.rows.item(i)
        list.push({
            id:row.id,
            firstName:row.firstname,
            lastName:row.lastname,
            age:row.age
        })
    }
    return list
}
