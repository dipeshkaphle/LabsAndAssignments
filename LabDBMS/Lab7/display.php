<html>
<style>

th,td {
    padding: 12px 15px;
}
td {
	justify-content: center;
	text-align: center;
}
table {
	border-collapse: collapse;
	margin: 25px 0;
	font-size: 0.9em;
    box-shadow: 0 0 20px rgba(0, 0, 0, 0.15);
}

thead tr {
    background-color: #009879;
    color: #ffffff;
    text-align: left;
}
tbody tr {
    border-bottom: 1px solid #dddddd;
}
tbody tr:last-of-type {
    border-bottom: 2px solid #009879;
}
input {
	margin: 5px;
}
h2,.container{
	display: flex;
	text-align: center;
	justify-content: center;
}
</style>
<body>

<h2>FILTER BY BLOOD GROUP</h2><br>
<div class="container">
	<form action="display.php" method="post">
		Blood Group: <input type="text" name="blood_group"><br>
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
	$dbconn = pg_connect("host=$servername dbname=$db_name user=$username 
		password=$password ");

	$qry = "SELECT * FROM DONORS WHERE DONORS.blood_grp='$_POST[blood_group]'";

	if ( ! $dbconn ){
		echo "Error during connection";
	}else{
		$result = pg_query( $qry);
		if ($result)
		{
			// Printing results in HTML
			echo "<div class=\"container\">";
			echo "<table s>\n";
			echo "<thead><br>";
			echo " <tr><th>Donor ID</th> <th>Aadhar No</th> ";
			echo "<th>Name </th> <th>Age</th> <th>Blood Group</th></tr>";
			echo "</thead><br><tbody>";
			while ($line = pg_fetch_array($result, null, PGSQL_ASSOC)) {
				echo "\t<tr>\n";
				foreach ($line as $col_value) {
					echo "\t\t<td>$col_value</td>\n";
				}
				echo "\t</tr>\n";
			}
			echo "</tbody>";
			echo "</table>\n";
			echo "</div>";

			pg_free_result($result);
			pg_close($dbconn);
		}else{
			echo "INSERTION FAILED";
		}
	}
}
?>


