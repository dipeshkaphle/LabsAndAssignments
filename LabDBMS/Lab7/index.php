<html>
<style>
input {
	margin: 5px;
}
h2,.container{
	display: flex;
	text-align: center;
	justify-content: center;
}
input{
	width: 100%;
}

</style>
<body>
<h2> Insert Entry </h2>
<div class="container">
	<form action="index.php" method="post">
		<table>
			<tr>
			<td>Donor ID :</td><td> <input type="number" name="donor_id"><br>
			</tr>
			<tr>
			<td>Name: </td><td><input type="text" name="name"></td>
			</tr>
			<tr>
				<td>Age :</td> <td><input type="number" name="age"></td>
			</tr>
			<tr>
				<td>Aadhar No : </td><td><input type="number" name="aadhar_no"></td>
			</tr>
			<tr>
				<td>Blood Group:</td> <td><input type="text" name="blood_group"></td>
			</tr>
		</table>
		<input type="submit" value="Submit">
	</form>
</div>

</body>
</html> 
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST" ){
	$servername = "localhost";
	$username = "dipesh";
	$password = "";
	$db_name = "dipesh";
	$insert_query= "INSERT INTO Donors VALUES($_POST[donor_id] ,
	    $_POST[aadhar_no],
	   '$_POST[name]',
	    $_POST[age],
       '$_POST[blood_group]')";
	$dbconn = pg_connect("host=$servername dbname=$db_name user=$username 
		password=$password ");

	if ( ! $dbconn ){
		echo "Error during connection";
	}else{
		$create_db = "CREATE TABLE IF NOT EXISTS 
			  Donors(Donor_ID INT PRIMARY KEY,
					 Aadhar_no INT,
					 Name VARCHAR(255),
					 Age INT,
                     Blood_grp VARCHAR(10))";
		$result = pg_query($create_db) ;
		if(!$result){
			echo "SCHEMA CREATION FAILED";
		}
		pg_free_result($result);
		$result = pg_query( $insert_query);
		if ($result)
		{
			pg_free_result($result);
			pg_close($dbconn);
			echo "<div class=\"container\">Successfully Inserted</div>";
		}else{
			echo "INSERTION FAILED";
		}
	}
}
?>

