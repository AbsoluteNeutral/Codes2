//------------------------------------------------------------ Voronoi Region Tests
VoronoiRegion::Type Gjk::IdentifyVoronoiRegion(const Vector3& q, const Vector3& p0,
	size_t& newSize, int newIndices[4],
	Vector3& closestPoint, Vector3& searchDirection)
{
	/******Student:Assignment5******/
	// Warn("Assignment5: Required function un-implemented");

	closestPoint = p0;
	searchDirection = q - closestPoint;
	newSize = 1;
	return VoronoiRegion::Point0;
}

VoronoiRegion::Type Gjk::IdentifyVoronoiRegion(const Vector3& q, const Vector3& p0, const Vector3& p1,
	size_t& newSize, int newIndices[4],
	Vector3& closestPoint, Vector3& searchDirection)
{
	/******Student:Assignment5******/
	//Warn("Assignment5: Required function un-implemented");

	float u = 0.0f;
	float v = 0.0f;
	BarycentricCoordinates(q, p0, p1, u, v);
	if (v <= 0) {
		closestPoint = p0;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 0;
		return VoronoiRegion::Point0;
	}
	else if (u <= 0) {
		closestPoint = p1;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 1;
		return VoronoiRegion::Point1;
	}

	closestPoint = u * p0 + v * p1;
	searchDirection = q - closestPoint;
	newIndices[0] = 0;
	newIndices[1] = 1;
	newSize = 2;
	return VoronoiRegion::Edge01;

}

VoronoiRegion::Type Gjk::IdentifyVoronoiRegion(const Vector3& q, const Vector3& p0, const Vector3& p1, const Vector3& p2,
	size_t& newSize, int newIndices[4],
	Vector3& closestPoint, Vector3& searchDirection)
{
	/******Student:Assignment5******/
	//Warn("Assignment5: Required function un-implemented");
	//float uAB = Math::PositiveMax(), vAB = Math::PositiveMax();
	//float uBC = Math::PositiveMax(), vBC = Math::PositiveMax();
	//float uCA = Math::PositiveMax(), vCA = Math::PositiveMax();

	float uAB = 0.0f, vAB = 0.0f;
	float uBC = 0.0f, vBC = 0.0f;
	float uCA = 0.0f, vCA = 0.0f;

	BarycentricCoordinates(q, p0, p1, uAB, vAB);
	BarycentricCoordinates(q, p1, p2, uBC, vBC);
	BarycentricCoordinates(q, p2, p0, uCA, vCA);

	float uABC = 0.0f, vABC = 0.0f, wABC = 0.0f;
	BarycentricCoordinates(q, p0, p1, p2, uABC, vABC, wABC);

	//Region A
	if (uCA <= 0.0f && vAB <= 0.0f) {
		closestPoint = p0;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 0;
		return VoronoiRegion::Point0;
	}
	//Region B
	else if (uAB <= 0.0f && vBC <= 0.0f) {
		closestPoint = p1;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 1;
		return VoronoiRegion::Point1;
	}
	//Region C
	else if (uBC <= 0.0f && vCA <= 0.0f) {
		closestPoint = p2;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 2;
		return VoronoiRegion::Point2;
	}
	//Region AB
	else if (uAB > 0.0f && vAB > 0.0f && wABC < 0.0f) {
		closestPoint = uAB * p0 + vAB * p1;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 0;
		newIndices[1] = 1;
		return VoronoiRegion::Edge01;
	}
	//Region BC
	else if (uBC > 0.0f && vBC > 0.0f && uABC < 0.0f) {
		closestPoint = uBC * p1 + vBC * p2;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 1;
		newIndices[1] = 2;
		return VoronoiRegion::Edge12;
	}
	//Region CA
	else if (uCA > 0.0f && vCA > 0.0f && vABC < 0.0f) {
		closestPoint = uCA * p2 + vCA * p0;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 0;
		newIndices[1] = 2;
		return VoronoiRegion::Edge02;
	}

	closestPoint = uABC * p0 + vABC * p1 + wABC * p2;
	searchDirection = q - closestPoint;
	newSize = 3;
	newIndices[0] = 0;
	newIndices[1] = 1;
	newIndices[2] = 2;
	return VoronoiRegion::Triangle012;
	// return VoronoiRegion::Unknown;
}

float ScalarTripleProduct(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
	// computes scalar triple product
	return Dot(a, Cross(b, c));
}
bool BarycentricCoordinates(const Vector3& point, const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& d,
	float& u, float& v, float& w, float& t, float epsilon = 0.0f)
{
	Vector3 ap{ point - a };
	Vector3 bp{ point - b };
	Vector3 ab{ b - a };
	Vector3 ac{ c - a };
	Vector3 ad{ d - a };
	Vector3 bc{ c - b };
	Vector3 bd{ d - b };
	//float a6 = ScalarTripleProduct(bp, bd, bc);
	//float b6 = ScalarTripleProduct(ap, ac, ad);
	//float c6 = ScalarTripleProduct(ap, ad, ab);
	//float d6 = ScalarTripleProduct(ap, ab, ac);
	float demo = 1.0f / ScalarTripleProduct(ab, ac, ad);
	if (demo > -epsilon && demo < epsilon) {
		//v = u = w = t = 0.0f;
		return false;
	}
	//u = ScalarTripleProduct(bp, bd, bc) * demo;
	v = ScalarTripleProduct(ap, ac, ad) * demo;
	w = ScalarTripleProduct(ap, ad, ab) * demo;
	t = ScalarTripleProduct(ap, ab, ac) * demo;
	u = 1.0f - w - v - t;
	if (v == 0.0f && u == 0.0f && w == 0.0f && t == 0.0f)
		return false;

	if (u < 0.0f)
		if (u < -epsilon) return false;
	if (v < 0.0f)
		if (v < -epsilon) return false;
	if (w < 0.0f)
		if (w < -epsilon) return false;
	if (t < 0.0f)
		if (t < -epsilon) return false;
	return true;
}

VoronoiRegion::Type Gjk::IdentifyVoronoiRegion(const Vector3& q, const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,
	size_t& newSize, int newIndices[4],
	Vector3& closestPoint, Vector3& searchDirection)
{
	/******Student:Assignment5******/
	//Warn("Assignment5: Required function un-implemented");
	float uAB = 0.0f, vAB = 0.0f;
	float uAC = 0.0f, vAC = 0.0f;
	float uAD = 0.0f, vAD = 0.0f;
	float uBC = 0.0f, vBC = 0.0f;
	float uBD = 0.0f, vBD = 0.0f;
	float uCD = 0.0f, vCD = 0.0f;
	BarycentricCoordinates(q, p0, p1, uAB, vAB);
	BarycentricCoordinates(q, p0, p2, uAC, vAC);
	BarycentricCoordinates(q, p0, p3, uAD, vAD);
	BarycentricCoordinates(q, p1, p2, uBC, vBC);
	BarycentricCoordinates(q, p1, p3, uBD, vBD);
	BarycentricCoordinates(q, p2, p3, uCD, vCD);

	float uABD = 0.0f, vABD = 0.0f, wABD = 0.0f;
	float uBCD = 0.0f, vBCD = 0.0f, wBCD = 0.0f;
	float uACB = 0.0f, vACB = 0.0f, wACB = 0.0f;
	float uADC = 0.0f, vADC = 0.0f, wADC = 0.0f;
	BarycentricCoordinates(q, p0, p1, p3, uABD, vABD, wABD);
	BarycentricCoordinates(q, p1, p2, p3, uBCD, vBCD, wBCD);
	BarycentricCoordinates(q, p0, p2, p1, uACB, vACB, wACB);
	BarycentricCoordinates(q, p0, p3, p2, uADC, vADC, wADC);

	float uABCD = 0.0f, vABCD = 0.0f, wABCD = 0.0f, tABCD = 0.0f;
	bool get = BarycentricCoordinates(q, p0, p1, p2, p3, uABCD, vABCD, wABCD, tABCD);


	//Region A
	if (vAB <= 0.0f && vAC <= 0.0f && vAD <= 0.0f) {
		closestPoint = p0;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 0;
		return VoronoiRegion::Point0;
	}
	//Region B
	else if (vBC <= 0.0f && vBD <= 0.0f && uAB <= 0.0f) {
		closestPoint = p1;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 1;
		return VoronoiRegion::Point1;
	}
	//Region C
	else if (uAC <= 0.0f && uBC <= 0.0f && vCD <= 0.0f) {
		closestPoint = p2;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 2;
		return VoronoiRegion::Point2;
	}
	//Region D
	else if (uAD <= 0.0f && uBD <= 0.0f && uCD <= 0.0f) {
		closestPoint = p3;
		searchDirection = q - closestPoint;
		newSize = 1;
		newIndices[0] = 3;
		return VoronoiRegion::Point3;
	}

	//Region AB
	else if (uAB > 0.0f && vAB > 0.0f
		&& vACB <= 0.0f && wABD <= 0.0f
		//&& wABCD > 0.0f && tABCD > 0.0f
		) {
		closestPoint = uAB * p0 + vAB * p1;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 0;
		newIndices[1] = 1;
		return VoronoiRegion::Edge01;
	}
	//Region AC
	else if (uAC > 0.0f && vAC > 0.0f
		&& wACB <= 0.0f && vADC <= 0.0f
		//&& vABCD > 0.0f && tABCD > 0.0f
		) {
		closestPoint = uAC * p0 + vAC * p2;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 0;
		newIndices[1] = 2;
		return VoronoiRegion::Edge02;
	}
	//Region AD
	else if (uAD > 0.0f && vAD > 0.0f
		&& vABD <= 0.0f && wADC <= 0.0f
		// && vABCD > 0.0f && wABCD > 0.0f
		) {
		closestPoint = uAD * p0 + vAD * p3;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 0;
		newIndices[1] = 3;
		return VoronoiRegion::Edge03;
	}
	//Region BC
	else if (uBC > 0.0f && vBC > 0.0f
		&& wBCD <= 0.0f && uACB <= 0.0f
		// && uABCD > 0.0f && tABCD > 0.0f
		) {
		closestPoint = uBC * p1 + vBC * p2;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 1;
		newIndices[1] = 2;
		return VoronoiRegion::Edge12;
	}
	//Region BD
	else if (uBD > 0.0f && vBD > 0.0f
		&& uABD <= 0.0f && vBCD <= 0.0f
		// && uABCD > 0.0f && wABCD > 0.0f
		) {
		closestPoint = uBD * p1 + vBD * p3;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 1;
		newIndices[1] = 3;
		return VoronoiRegion::Edge13;
	}
	//Region CD
	else if (uCD > 0.0f && vCD > 0.0f
		&& uADC <= 0.0f && uBCD <= 0.0f
		//  && uABCD > 0.0f && vABCD > 0.0f
		) {
		closestPoint = uCD * p2 + vCD * p3;
		searchDirection = q - closestPoint;
		newSize = 2;
		newIndices[0] = 2;
		newIndices[1] = 3;
		return VoronoiRegion::Edge23;
	}
	//Region ABD
	else if (uABD > 0.0f && vABD > 0.0f  && wABD > 0.0f
		&& wABCD <= 0.0f
		) {
		closestPoint = uABD * p0 + vABD * p1 + wABD * p3;
		searchDirection = q - closestPoint;
		newSize = 3;
		newIndices[0] = 0;
		newIndices[1] = 1;
		newIndices[2] = 3;
		return VoronoiRegion::Triangle013;
	}
	//Region BCD
	else if (uBCD > 0.0f && vBCD > 0.0f  && wBCD > 0.0f
		&& uABCD <= 0.0f
		) {
		closestPoint = uBCD * p1 + vBCD * p2 + wBCD * p3;
		searchDirection = q - closestPoint;
		newSize = 3;
		newIndices[0] = 1;
		newIndices[1] = 2;
		newIndices[2] = 3;
		return VoronoiRegion::Triangle123;
	}
	//Region ACB
	else if (uACB > 0.0f && vACB > 0.0f  && wACB > 0.0f
		&& tABCD <= 0.0f
		) {
		closestPoint = uACB * p0 + vACB * p2 + wACB * p1;
		searchDirection = q - closestPoint;
		newSize = 3;
		newIndices[0] = 0;
		newIndices[1] = 1;
		newIndices[2] = 2;
		return VoronoiRegion::Triangle012;
	}
	//Region ADC
	else if (uADC > 0.0f && vADC > 0.0f  && wADC > 0.0f
		&& vABCD <= 0.0f
		) {
		closestPoint = uADC * p0 + vADC * p3 + wADC * p2;
		searchDirection = q - closestPoint;
		newSize = 3;
		newIndices[0] = 0;
		newIndices[1] = 2;
		newIndices[2] = 3;
		return VoronoiRegion::Triangle023;
	}

	closestPoint = uABCD * p0 + vABCD * p1 + wABCD * p2 + tABCD * p3;
	searchDirection = q - closestPoint;
	if (!((searchDirection.x > 0.0f && searchDirection.y > 0.0f && searchDirection.z > 0.0f)))
		searchDirection = Vector3{ 0.0f, 0.0f, 0.0f };
	newSize = 4;
	newIndices[0] = 0;
	newIndices[1] = 1;
	newIndices[2] = 2;
	newIndices[3] = 3;
	return VoronoiRegion::Tetrahedra0123;
}