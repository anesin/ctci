SELECT BuildingName FROM Buildings
INNER JOIN (
    SELECT BuildingID, COUNT(BuildingID) as Cnt FROM Apartments
    INNER JOIN Requests
    ON Status = 'Open' AND Requests.AptID = Apartments.AptID
    GROUP BY BuildingID
) BuildingIDs
ON BuildingIDs.BuildingID = Buildings.BuildingID
ORDER BY BuildingName;